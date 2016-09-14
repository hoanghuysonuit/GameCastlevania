#include "Class\Framework\Windows.h"


LRESULT CALLBACK WinProc_(HWND WindowsHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(WindowsHandle, Message, wParam, lParam);
}

CWindows::CWindows(HINSTANCE hInstance, LPWSTR Name, bool isWindowed)
{
	this->m_ScreenHeight	= BACKBUFFER_HEIGHT;
	this->m_ScreenWidth		= BACKBUFFER_WIDTH;
	this->m_hInstance		= hInstance;
	this->m_IsWindowed		= isWindowed;
	this->m_Name			= Name;

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	this->m_hInstance = hInstance;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.hInstance		= this->m_hInstance;
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpfnWndProc	= (WNDPROC)WinProc_;
	wcex.lpszClassName	= m_Name;

	RegisterClassEx(&wcex);

	this->m_hWnd = CreateWindow(m_Name, 
								m_Name,
								m_IsWindowed ? WS_OVERLAPPEDWINDOW :(WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP),
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								m_ScreenWidth, m_ScreenHeight,
								NULL, NULL,
								this->m_hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}


CWindows::~CWindows(void)
{
}


void CWindows::initWindowGame()
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed			= m_IsWindowed ? TRUE : FALSE;
	d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat	= D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount	= 1;
	d3dpp.BackBufferHeight	= m_ScreenHeight;
	d3dpp.BackBufferWidth	= m_ScreenWidth;

	HRESULT hr = m_d3d->CreateDevice(
									D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									m_hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&m_d3dDevice);

	if (FAILED(hr))
		return;

	hr = D3DXCreateSprite(m_d3dDevice, &m_SpriteHandler);

	if (FAILED(hr))
		return;

}

bool CWindows::startDraw()
{
	if (m_d3dDevice == 0) {
		return false;
	}
	else {
		m_d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0);
		m_d3dDevice->BeginScene();
		m_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		return true;
	}
}

bool CWindows::stopDraw()
{
	m_SpriteHandler->End();
	m_d3dDevice->EndScene();
	m_d3dDevice->Present(0, 0, 0, 0);
	return true;
}

LPD3DXSPRITE CWindows::getSpriteHandler() {
	return m_SpriteHandler;
}

HWND CWindows::getWindowHandler() {
	return m_hWnd;
}

LPDIRECT3DDEVICE9 CWindows::getDevice() {
	return m_d3dDevice;
}