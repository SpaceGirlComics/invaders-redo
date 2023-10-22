#include "includes.h"

DXInput::DXInput(HWND _hWnd)
{
	DIObject = NULL;
	DIKeyboardDevice = NULL; 
	if(!InitDirectInput())
	{
		MessageBox(NULL, L"Direct Input failed", NULL, NULL);
	}
	else if(!InitKeyboard(_hWnd))
	{
		MessageBox(NULL, L"Unable to aquire Keyboard", NULL, NULL);
	}
	for(int x = 0; x<256; x++)
	{
		oldkeys[x]=false;
	}
}

DXInput::~DXInput()
{
	if(DIKeyboardDevice)
	{
		DIKeyboardDevice->Unacquire(); //unacquire device (NEW)
		DIKeyboardDevice->Release();   //release keyboard stuff (NEW)
		DIKeyboardDevice = NULL;       //pointer to NULL (NEW)
	}

	if(DIObject)
	{
		DIObject->Release(); //release main object
		DIObject = NULL;
	}
} 

bool DXInput::InitDirectInput()
{
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&DIObject, NULL)))
	{
		return false;
	}
	return true;
} 

bool DXInput::InitKeyboard(HWND _hWnd)
{
	if(FAILED(DIObject->CreateDevice(GUID_SysKeyboard, &DIKeyboardDevice, NULL)))
	{
		return false;
	}
	if(FAILED(DIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}
	if(FAILED(DIKeyboardDevice->SetCooperativeLevel(_hWnd, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND)))
	{
		return false;
	}
	if(FAILED(DIKeyboardDevice->Acquire()))
	{
		return false;
	}
	return true;
}

bool DXInput::UpDate()
{
	for(int x = 0; x<256; x++)
	{
		oldkeys[x]=keys[x];
	}
	if(FAILED(DIKeyboardDevice->GetDeviceState(sizeof(keys), (LPVOID)&keys)))
	{
		return false;
	}
	return true;
}

bool DXInput::KeyDown(int Key)
{
	return(keys[Key]);
}

bool DXInput::KeyUp(int Key)
{
	if(!keys[Key])
	{
		return(keys[Key]!=oldkeys[Key]);
	}
	return(false);
}

void DXInput::SetFalse(int Key)
{
	keys[Key] = false;
}