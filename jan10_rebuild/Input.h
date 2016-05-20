#pragma once
#include "Common.h"

#include <XInput.h>
#pragma comment(lib, "xinput9_1_0.lib")


#define USE_KEYBOARD_MOUSE
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


class Input {

public:

	Input(HWND & hwnd, HINSTANCE& hInstance);
	~Input();


	void Update(float time);


	IDirectInputDevice8A* GetMouse();
	IDirectInputDevice8A* GetKeyboard();

	void SetLastState(DIMOUSESTATE);



	bool IsPressed(INPUTVALUES iv);

	float GetMouseX();
	float GetMouseY();

	XMFLOAT2& GetMousePosition();
	XMFLOAT2& GetMouseDelta();

	void Resize();



private:


	IDirectInput8A* m_DI;
	IDirectInputDevice8A* m_Keyboard;
	IDirectInputDevice8A* m_Mouse;

	unsigned char m_Keybuffer[256];
	_DIMOUSESTATE2 m_MouseState;

	XMFLOAT2 m_MousePosition;
	XMFLOAT2 m_MouseDelta;

	bool m_Up_Bool;
	bool m_Down_Bool;
	bool m_Left_Bool;
	bool m_Right_Bool;
	bool m_Raise_Bool;
	bool m_Lower_Bool;
	bool m_RotateLeft_Bool;
	bool m_RotateRight_Bool;

	HWND& m_HWnd;
	LONG m_ClientWidth;
	LONG m_ClientHeight;



};

