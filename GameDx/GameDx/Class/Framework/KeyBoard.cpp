#include "KeyBoard.h"
#include <InitGuid.h>

CKeyBoard::CKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	this->m_Instance	= hInstance;
	this->m_hWnd		= hWnd;

	HRESULT hr = DirectInput8Create(m_Instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&this->m_dInput, NULL);
	if (hr != DI_OK)
		return;
	hr = m_dInput->CreateDevice(GUID_SysKeyboard, &this->m_KeyBoard, NULL);
	if (hr != DI_OK)
		return;
	hr = m_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK)
		return;
	hr = m_KeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK)
		return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= KEYBOARD_BUFFER_SIZE;

	hr = m_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK)
		return;

	hr = m_KeyBoard->Acquire();
	if (hr != DI_OK)
		return;

}

CKeyBoard::~CKeyBoard()
{
	if (m_KeyBoard)
	{
		m_KeyBoard->Unacquire();
		m_KeyBoard->Release();
	}

	if (m_dInput) 
		m_dInput->Release();
}

void CKeyBoard::Update()
{
	// Collect all key states first
	memcpy(m_preKeyState, m_KeyState, sizeof(m_KeyState));

	HRESULT result = m_KeyBoard->GetDeviceState(sizeof(m_KeyState), m_KeyState);
	if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		m_KeyBoard->Acquire();
}

bool CKeyBoard::KeyPress(int KeyCode)
{
	if (ISKEYDOWN(m_preKeyState[KeyCode]) == 0)
		return ISKEYDOWN(m_KeyState[KeyCode]) > 0;
	return false;
}

bool CKeyBoard::KeyUp(int KeyCode)
{
	return (ISKEYDOWN(m_KeyState[KeyCode]) == 0);
}

bool CKeyBoard::KeyDown(int KeyCode)
{
	if (ISKEYDOWN(m_preKeyState[KeyCode]) > 0)
		return ISKEYDOWN(m_KeyState[KeyCode]) > 0;
	return false;
}

bool CKeyBoard::KeyRelease(int KeyCode)
{
	if (ISKEYDOWN(m_KeyState[KeyCode]) > 0)
		return KeyUp(m_preKeyState[KeyCode]);
	return false;
}