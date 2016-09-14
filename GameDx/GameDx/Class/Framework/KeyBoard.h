/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/

#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include "Class\Game\Utill\stdafx.h"

class CKeyBoard
{
public:
	CKeyBoard(HINSTANCE hInstance, HWND hWnd);
	~CKeyBoard();

	void Update();

	bool KeyPress	(int KeyCode);
	bool KeyDown	(int KeyCode);
	bool KeyUp		(int KeyCode);
	bool KeyRelease	(int KeyCode);

private:
	HINSTANCE				m_Instance;
	HWND					m_hWnd;
	LPDIRECTINPUT8			m_dInput;
	LPDIRECTINPUTDEVICE8	m_KeyBoard;
	BYTE					m_KeyState[256];
	BYTE					m_preKeyState[256];
};

#endif
