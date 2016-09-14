#include "Text.h"

CText*				CText::m_Instance			= NULL;
LPDIRECT3DDEVICE9	CText::m_Device				= 0;
LPD3DXSPRITE		CText::m_SpriteHandle		= 0;
LPD3DXFONT			CText::m_Font				= 0;

CText::CText()
{
	m_FontFace				= DEFAULT_FONTNAME;
	m_FontSize				= DEFAULT_FONT_SIZE;

	AddFontResourceEx(DEFAULT_FONTPATH, FR_PRIVATE, 0);

}

CText::CText(LPCTSTR fontFace,LPCTSTR fontPath, int fontSize)
{
	m_FontFace				= fontFace;
	m_FontSize				= fontSize;

	AddFontResourceEx(fontPath, FR_PRIVATE, 0);

}

void CText::InitFont()
{
	HRESULT hr = D3DXCreateFont(
							m_Device,
							m_FontSize,
							0, 400, 0, false,
							DEFAULT_CHARSET,
							OUT_TT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							DEFAULT_PITCH,
							m_FontFace,
							&(m_Font));
	if (FAILED(hr))
		return;
}

CText::~CText()
{
	if (m_Font != NULL)
	{
		m_Font->Release();
		m_Font = NULL;
	}
}

void CText::InitDevice(LPDIRECT3DDEVICE9 device, LPD3DXSPRITE spriteHandle)
{						
	m_Device			= device;
	m_SpriteHandle		= spriteHandle;
};


//template<class T>
void CText::Draw(const wchar_t* Content, D3DXVECTOR3 Position, D3DCOLOR Color, int Size, UINT DT_Type, wchar_t* FontFace)
{
	if (Size != m_FontSize || FontFace != m_FontFace)
		setChange(Size, FontFace);

	D3DXVECTOR3 pos(Position);

	RECT drawField;
	drawField = { pos.x, pos.y, 0, 0 };

	//http://stackoverflow.com/questions/1655242/lpd3dxfont-drawtext-using-dt-calcrect

	m_Font->DrawText(m_SpriteHandle, Content,
		-1, &drawField, DT_CALCRECT, Color);

	if (DT_Type == DT_CENTER)
	{
		LONG w				 = drawField.right - drawField.left;
		drawField.left		-= (LONG)(w / 2.0F);
		drawField.right		-= (LONG)(w / 2.0F);
	}
	else if (DT_Type == DT_RIGHT)
	{
		LONG w				 = drawField.right - drawField.left;
		drawField.left		-= w;
		drawField.right		-= w;
	}

	m_Font->DrawText(m_SpriteHandle, Content,
		-1, &drawField, DT_Type, Color);
};

void CText::setChange(int fontSize, LPCTSTR fontFace)
{
	m_Font->Release();
	m_FontSize			= fontSize;
	m_FontFace			= fontFace;
	this->m_Instance	= new CText(m_FontFace, findFontPath(m_FontFace), m_FontSize);
	m_Instance->InitFont();
}

LPCTSTR CText::findFontPath(LPCTSTR fontFace)
{
	if (fontFace == DEFAULT_FONTNAME)
		return DEFAULT_FONTPATH;
	return DEFAULT_FONTPATH;
}

CText* CText::getInstace()
{
	if (!m_Instance)
	{
		m_Instance = new CText();
		m_Instance->InitFont();
	}
	return m_Instance;
}