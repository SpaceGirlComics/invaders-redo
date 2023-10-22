#include "includes.h"

DX3D::DX3D()
{
}

DX3D::~DX3D()
{
	if(pD3D)
	{
		pD3D->Release();
	}
	if(pDevice)
	{
		pDevice->Release();
	}
}

bool DX3D::InitD3D(int _width, int _height, 
				   int _PositionX, int _PositionY, 
				   LPCWSTR _WndClass, LPCWSTR _WndTitle, HWND _hWnd)
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
	_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &PresentParameters, &pDevice)))
	{
		return false;
	}

	D3DXMATRIX mat;

	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/6.0f, _height/_width, 1.0f, 100.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);
	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);

	D3DXMatrixTranslation(&mat, 0, 0, 10.0);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_PYRAMIDALQUAD);
	pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_PYRAMIDALQUAD);
	pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	return true;
}

LPDIRECT3DDEVICE9 DX3D::getDevice()
{
	return(pDevice);
}