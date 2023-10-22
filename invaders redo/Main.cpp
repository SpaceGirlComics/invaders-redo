#include "includes.h"

HINSTANCE g_hInst; // Handle to the instance of our program
HWND g_hWnd; // Handle to the window
HRESULT g_hr; // Variable to hold function call results
LPCWSTR g_WndClass, g_WndName;
int g_PositionX, g_PositionY, g_SizeX, g_SizeY;
LPDIRECT3D9 pD3D;
LPDIRECT3DDEVICE9 pDevice; 
bool keys[256];
bool done;
DWORD state;
bullets* head;
bullets* current;
CAlien* mother;
CAlien* drone;
DXInput* InputDX;
Cship ship;
IDirect3DTexture9* CAlien::g_pTexture;
IDirect3DTexture9* CTitle::g_pTexture;
IDirect3DTexture9* COver::g_pTexture;
IDirect3DTexture9* CWinScreen::g_pTexture;


int	bullets::userCount;
int bullets::myTicks;
int Cship::myTicks;
int CAlien::myTicks;

bool InitD3D()
{
//	callcount=0;
    if((pD3D = Direct3DCreate9(D3D_SDK_VERSION))==NULL)
	{
        return false;
    }
    D3DDISPLAYMODE DisplayMode;
    pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);
    D3DPRESENT_PARAMETERS PresentParameters;
    ZeroMemory(&PresentParameters, sizeof(D3DPRESENT_PARAMETERS));
    PresentParameters.BackBufferFormat = DisplayMode.Format;
    PresentParameters.Windowed = true;
    PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    if(FAILED(pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
    g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &PresentParameters, &pDevice)))
	{
        return false;
    }

	D3DXMATRIX mat;

	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/6.0f, g_SizeY/g_SizeX, 1.0f, 100.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);
	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);

	D3DXMatrixTranslation(&mat, 0, 0, 10.0);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	D3DXCreateTextureFromFile(pDevice, L"Over.bmp", &COver::g_pTexture);
	D3DXCreateTextureFromFile(pDevice, L"invaders.bmp", &CAlien::g_pTexture);
	D3DXCreateTextureFromFile(pDevice, L"Title.bmp", &CTitle::g_pTexture);
	D3DXCreateTextureFromFile(pDevice, L"win.bmp", &CWinScreen::g_pTexture);

	InputDX = new DXInput(g_hWnd);

    return true;
}

//The windows message handler
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        break;
        case WM_KEYDOWN: 
            keys[wParam]=true;
   			return 0;
		case WM_KEYUP:
 			keys[wParam]=false;
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);

    }
}

bool MainWnd(int _width, int _height, int _PositionX, int _PositionY, LPCWSTR _WndClass, LPCWSTR _WndTitle)
{
	g_SizeX = _width;
	g_SizeY = _height;
	g_PositionX = _PositionX;
	g_PositionY = _PositionY;
	g_WndClass = _WndClass;
	g_WndName = _WndTitle;

	for(int x=0; x<256; x++)
	{
		keys[x]=false;
	}

	WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_OWNDC | CS_HREDRAW | CS_VREDRAW, WinProc, 0, 0, 
                     GetModuleHandle(NULL), NULL, NULL, (HBRUSH)GetStockObject(LTGRAY_BRUSH), NULL,
                     _WndClass, NULL};
	
	if(!RegisterClassEx(&wc))
	{
		return(false);
	}

	  //Create the application's window
    g_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, 
							_WndClass, _WndTitle, 
                            WS_VISIBLE | WS_OVERLAPPED |WS_SYSMENU|WS_MINIMIZEBOX, 
							_PositionX, _PositionY, 
							_width, _height,
                            NULL, NULL, 
							GetModuleHandle(NULL), 
							NULL);
	
	if(!g_hWnd)
	{
		return(false);
	}
	if(!InitD3D())
	{
		return(false);
	}
	return(true);
}

void RenderScene()
{
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0 );
	pDevice->BeginScene();
	pDevice->SetFVF(D3DFVF_CVertex);
	switch(state)
	{
		case STATE_VICTORY:
		{
			CWinScreen win;
			pDevice->SetTexture(0, CWinScreen::g_pTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, win.vtx, sizeof(Vertex));
			break;
		}
		case STATE_OVER:
		{
			COver over;
			pDevice->SetTexture(0, COver::g_pTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, over.vtx, sizeof(Vertex));
			break;
		}
		case STATE_TITLE:
		{
			CTitle title;
			pDevice->SetTexture(0, CTitle::g_pTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, title.vtx, sizeof(Vertex));
			break;
		}
		case STATE_GAMEPLAY:
		{
			pDevice->SetTexture(0, NULL);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, ship.vtx, sizeof(Vertex));
			while(current)
			{
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, current->vtx, sizeof(Vertex));
				current=current->next;
			}
			pDevice->SetTexture(0, CAlien::g_pTexture);
			while(drone)
			{
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, drone->vtx, sizeof(Vertex));
				drone=drone->next;
			}
			drone=mother;
			current=head;
			break;
		}
	}
	pDevice->EndScene();
	pDevice->Present(NULL,NULL,NULL,NULL);
} 

//Application entry point
void playerControl()
{
	InputDX->UpDate();

	if(keys[VK_ESCAPE])
	{
		if(state == STATE_GAMEPLAY)
		{
			doTitle();
		}
		else
		{
			SendMessage(g_hWnd, WM_CLOSE, NULL, NULL);
		}
		keys[VK_ESCAPE]=false;
	}
	if(keys[VK_RETURN])
	{
		if(state== STATE_TITLE)
		{
			InitGame();
			keys[VK_RETURN] = false;
		}
		else if(state == STATE_OVER || state == STATE_VICTORY)
		{
			doTitle();
			keys[VK_RETURN] = false;
		}
	}
	if(InputDX->KeyDown(DIK_LEFT)&&(state == STATE_GAMEPLAY))
	{
		if(GetTickCount() - Cship::myTicks > 1)
		{
			Cship::myTicks = GetTickCount();
			if(ship.vtx[1].fX>-2.65f)
			{
				ship.moving(-0.06f);
			}
		}
	}
	if(InputDX->KeyDown(DIK_RIGHT)&&(state == STATE_GAMEPLAY))
	{
		if(GetTickCount() - Cship::myTicks > 1)
		{
			Cship::myTicks = GetTickCount();
			if(ship.vtx[1].fX<2.656f)
			{
				ship.moving(0.06f);
			}
		}
	}
	if(InputDX->KeyDown(DIK_SPACE))
	{
		if(!ship.fired)
		{
			if(state == STATE_GAMEPLAY)
			{
				ship.fired=true;
				if(head)
				{
					while(current->next)
					{
						current=current->next;
					}
					if(bullets::userCount <2)
					{
  						current->next=ship.fire();
 						current->next->prev=current;
						current->next->next=NULL;
					}
				}
				else
				{
  					head = ship.fire();
					head->prev = head->next = NULL;
				}
				current = head;
			}
		}
	}
	if(InputDX->KeyUp(DIK_SPACE))
	{
		ship.fired=false;
	}
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, 
					int nCmdShow)
{
	srand((unsigned int)GetTickCount());
	if(!MainWnd(640, 800, 300, 0, L"SPACEGIRL", L"Invaders!"))
	{
		MessageBox(NULL, NULL, L"Unable to Create Window.", NULL);
		return(-1);
	}
	doTitle();
	CAlien::myTicks = bullets::myTicks = Cship::myTicks = GetTickCount();
	MSG msg;
	done = false;
	g_hInst= hInst;
	bullets::userCount=0;
	state = STATE_TITLE;
	//Start game running: Enter the game loop
	while(!done)
	{
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg); 

			if (msg.message == WM_QUIT)
			{
				done=!done;
				break;
			}
		}
		if(state == STATE_GAMEPLAY)
		{
			if( GetTickCount() - bullets::myTicks >20)
			{
				bullets::myTicks = GetTickCount();
				bulletMakeAndMove();
			}
			if(GetTickCount() - CAlien::myTicks > 150)
			{
				CAlien::myTicks = GetTickCount();
				moveAliens();
			}
			if(!mother)
			{
				state = STATE_VICTORY;
				KillCurrentBoard();
			}
		}
		RenderScene();
		playerControl();
		bulletShipCollision();
		bulletAlienCollision();
		checkPlanetFall();
	}
    KillCurrentBoard();
	delete(InputDX);
    return 0;
}

