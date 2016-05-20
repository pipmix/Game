#include "Input.h"


Input::Input(HWND & hwnd, HINSTANCE& hInstance): m_HWnd(hwnd) {


	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DI, nullptr);
	m_DI->CreateDevice(GUID_SysKeyboard, &m_Keyboard, nullptr);
	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_Keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 10;

	m_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	m_DI->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr);
	m_Mouse->SetDataFormat(&c_dfDIMouse2);
	m_Mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);



	m_Up_Bool = false;

	Resize();
}

Input::~Input() {

	m_Keyboard->Unacquire();
	m_Mouse->Unacquire();
	m_DI->Release();
	m_Keyboard = nullptr;
	m_Mouse = nullptr;
	m_DI = nullptr;

}




void Input::Update(float time) {
	m_Up_Bool = false;
	m_Down_Bool = false;
	m_Left_Bool = false;
	m_Right_Bool = false;
	m_Raise_Bool = false;
	m_Lower_Bool = false;
	m_RotateLeft_Bool = false;
	m_RotateRight_Bool = false;


	memset(&m_MouseState, 0, sizeof(DIMOUSESTATE2));
	memset(m_Keybuffer, 0, sizeof(m_Keybuffer));

	m_Mouse->Acquire();
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_MouseState);
	m_Keyboard->Acquire();
	m_Keyboard->GetDeviceState(sizeof(m_Keybuffer), m_Keybuffer);


	
	

	if (m_Keybuffer[DIK_W] & 0x80) m_Up_Bool = true;
	if (m_Keybuffer[DIK_S] & 0x80) m_Down_Bool = true;
	if (m_Keybuffer[DIK_A] & 0x80) m_Left_Bool = true;
	if (m_Keybuffer[DIK_D] & 0x80) m_Right_Bool = true;
	if (m_Keybuffer[DIK_Q] & 0x80) m_Lower_Bool = true;
	if (m_Keybuffer[DIK_E] & 0x80) m_Raise_Bool = true;
	if (m_Keybuffer[DIK_Z] & 0x80) m_RotateLeft_Bool = true;
	if (m_Keybuffer[DIK_X] & 0x80) m_RotateRight_Bool = true;



	float xx = m_MouseState.lX;
	float yy = m_MouseState.lY;


	m_MouseDelta = XMFLOAT2(0.0f,0.0f);
	m_MouseDelta.x = m_MousePosition.x - xx;
	m_MouseDelta.y = m_MousePosition.y - yy;


	m_MouseDelta.x = xx - (static_cast<float>(m_ClientWidth) / 2);
	m_MouseDelta.y = yy - (static_cast<float>(m_ClientHeight) / 2);
	m_MousePosition = XMFLOAT2(xx, yy);

}


bool Input::IsPressed(INPUTVALUES iv) {

	switch (iv) {

		case INPUT_UP: 
			if (m_Up_Bool == 1)return true;
			else return false;
			break;
		case INPUT_DOWN:
			if (m_Down_Bool == 1)return true;
			else return false;
			break;
		case INPUT_LEFT:
			if (m_Left_Bool == 1)return true;
			else return false;
			break;
		case INPUT_RIGHT:
			if (m_Right_Bool == 1)return true;
			else return false;
			break;
		case INPUT_RAISE:
			if (m_Raise_Bool == 1)return true;
			else return false;
			break;
		case INPUT_LOWER:
			if (m_Lower_Bool == 1)return true;
			else return false;
			break;
		case INPUT_ROTATELEFT:
			if (m_RotateLeft_Bool == 1)return true;
			else return false;
			break;
		case INPUT_ROTATERIGHT:
			if (m_RotateRight_Bool == 1)return true;
			else return false;
			break;

		default:
			return false;
			break;
	}

}


XMFLOAT2& Input::GetMousePosition() {
	return m_MousePosition;
}

XMFLOAT2& Input::GetMouseDelta() {
	return m_MouseDelta;
}


void Input::Resize() {

	RECT rc = { 0,0,0,0 };
	GetClientRect(m_HWnd, &rc);
	m_ClientWidth = rc.right;
	m_ClientHeight = rc.bottom;

	

}