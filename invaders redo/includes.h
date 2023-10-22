#ifndef INCLUDES_H
#define INCLUDES_H
	#define STATE_TITLE    0x00000002
	#define STATE_GAMEPLAY 0x00000004
	#define STATE_OVER     0x00000008 
	#define STATE_VICTORY  0x00000020
	#ifndef VC_EXTRALEAN
		#define VC_EXTRALEAN
	#endif
	
	#ifndef DIRECTXHASARRIVED
		#define DIRECTXHASARRIVED
		#include <d3d9.h>
		#include <D3dx9math.h>
		#include <D3dx9tex.h>
		#include <dinput.h>
		#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3d9.lib")
		#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3dx9.lib")
		#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\dinput8.lib")
		#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\dxguid.lib")
	#endif

	#ifndef D3DFVF_CVertex
		#define D3DFVF_CVertex (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#endif

	#include "Vertex.h"
	#include "Bullets.h"
	#include "Alien.h"
	#include "Ship.h"
	#include "Title.h"
	#include "Over.h"
	#include "win.h"
	#include "DXInput.h"

	extern HINSTANCE g_hInst; // Handle to the instance of our program
	extern HWND g_hWnd; // Handle to the window
	extern HRESULT g_hr; // Variable to hold function call results
	extern LPCWSTR g_WndClass, g_WndName;
	extern int g_PositionX, g_PositionY, g_SizeX, g_SizeY;
	extern LPDIRECT3D9 pD3D;
	extern LPDIRECT3DDEVICE9 pDevice; 
	extern IDirect3DTexture9 *g_pTexture, *g_pTexture2;
	extern bool keys[256];
	extern bool done;
	extern DWORD state;
	extern bullets* head;
	extern bullets* current;
	extern CAlien* mother;
	extern CAlien* drone;
	extern Cship ship;

	bool doTitle();
	bool InitGame();
	void KillCurrentBoard();
	void bulletAlienCollision();
	void bulletShipCollision();
	void bulletMakeAndMove();
	void moveAliens();
	bool checkPlanetFall();
	void doOverScreen();
#endif