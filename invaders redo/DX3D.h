#ifndef DX3D_H
#define DX3D_H

#include <d3d9.h>
#include <d3dx9math.h>
#include <D3dx9tex.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")


class DX3D
{
	public:
		DX3D();
		~DX3D();		
		bool InitD3D(int _width, int _height, 
			int _PositionX, int _PositionY, 
			LPCWSTR _WndClass, LPCWSTR _WndTitle, HWND _hWnd);
		LPDIRECT3DDEVICE9 getDevice();
		
	protected:
		LPDIRECT3D9 pD3D; // d3d interface pointer
		static LPDIRECT3DDEVICE9 pDevice; // d3d device pointer
};
#endif