/****************************************************************************/
/* Create by Michael Le*/
/* 08/07/2015 */
/***************************************************************************/

#ifndef __TEXT_H__
#define __TEXT_H__

#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"

class CText
{
public:
	CText();
	CText(LPCTSTR, LPCTSTR, int);
	~CText();

				void				Draw(const wchar_t *Content, D3DXVECTOR3 Position, D3DCOLOR Color = DEFAULT_FONT_COLOR, int Size = DEFAULT_FONT_SIZE, UINT DT_Type = DT_LEFT, wchar_t* FontFace = DEFAULT_FONTNAME);
				void				InitFont();
				void				setChange(int fontSize = DEFAULT_FONT_SIZE, LPCTSTR fontFace = DEFAULT_FONTNAME);
				LPCTSTR				findFontPath(LPCTSTR FontFace);
	
	static		void				InitDevice(LPDIRECT3DDEVICE9, LPD3DXSPRITE);
	static		CText*				getInstace();

private:
	static		LPDIRECT3DDEVICE9	m_Device;
	static		LPD3DXSPRITE		m_SpriteHandle;
	static		LPD3DXFONT			m_Font;
				int					m_FontSize;
				LPCTSTR				m_FontFace;

private:
	static		CText*				m_Instance;


};

#endif

