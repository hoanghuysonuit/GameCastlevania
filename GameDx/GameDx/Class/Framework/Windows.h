/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/

#ifndef __CWINDOWS_H__
#define __CWINDOWS_H__

#include "Class\Game\Utill\stdafx.h"

class CWindows
{
private:
	HINSTANCE				m_hInstance;
	HWND					m_hWnd;

	LPDIRECT3D9				m_d3d;
	LPDIRECT3DDEVICE9		m_d3dDevice;
	LPD3DXSPRITE			m_SpriteHandler;

	int						m_ScreenWidth;
	int						m_ScreenHeight;
	int						m_IsWindowed;
	LPWSTR					m_Name;
public:
	
	LPD3DXSPRITE			getSpriteHandler();
	HWND					getWindowHandler();
	LPDIRECT3DDEVICE9		getDevice();

	void					initWindowGame();
	bool					startDraw();
	bool					stopDraw();

	CWindows(HINSTANCE hInstance, LPWSTR Name = WINDOWS_NAME, bool isWindowed = 1);
	~CWindows(void);
};

#endif
