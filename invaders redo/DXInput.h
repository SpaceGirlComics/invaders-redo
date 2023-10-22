#ifndef DXINPUT_H
#define DXINPUT_H
#include <dinput.h>
//#include <Dinput.h>

class DXInput
{
	public:
		DXInput(HWND _hWnd);
		~DXInput();
		bool InitDirectInput();
		bool InitKeyboard(HWND _hWnd);
		bool UpDate();
		bool KeyDown(int Key);
		bool KeyUp(int Key);
		void SetFalse(int Key);
	private:
		LPDIRECTINPUT8 DIObject;
		LPDIRECTINPUTDEVICE8 DIKeyboardDevice;
		bool keys[256];
		bool oldkeys[256];
};
#endif