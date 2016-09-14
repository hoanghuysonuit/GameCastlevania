/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/

#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "Class\Game\Utill\stdafx.h"

class CSprite
{
public:
	static void		initSpriteHandler(LPD3DXSPRITE spriteHandler);
public:
	CSprite(wstring filePath, int nRows = 1, int nColumns = 1, int nFrames = 1, int Index = 0);
	CSprite(const CSprite& source);
	~CSprite(void);

	bool			Render(
							D3DXVECTOR3 Position	= D3DXVECTOR3(0, 0, 0.5),
							D3DXVECTOR2 scale		= D3DXVECTOR2(1.0f, 1.0f),
							float		rotate		= 0,
							int			draw_center = DRAWCENTER_MIDDLE_BOTTOM,
							bool		isLoop		= true,
							float		FPSs		= 60,
							D3DCOLOR	fade		= D3DCOLOR_XRGB(255, 255, 255)
						  );

	bool			Render(
							int			fromFrame	= 1,
							int			toFrame		= 1,
							D3DXVECTOR3 Position	= D3DXVECTOR3(0, 0, 0.5),
							D3DXVECTOR2 scale		= D3DXVECTOR2(1.0f, 1.0f),
							float		rotate		= 0,
							int			draw_center = DRAWCENTER_MIDDLE_BOTTOM,
							bool		isLoop		= true,
							float		FPSs		= 60,
							D3DCOLOR	fade		= D3DCOLOR_XRGB(255, 255, 255)
							);


	RECT			getScrRect();
	D3DXVECTOR3		setCenter(int drawcenter);

	void			Next();
	void			Reset();
	int				getIndex();
	bool			isCompleted(int);

	D3DXIMAGE_INFO	getFrameInfo();
	D3DXVECTOR2		getScale();

private:
	static	LPD3DXSPRITE			m_spriteHandler;
	static	LPDIRECT3DDEVICE9		m_d3dDevice;
	static	vector<CSprite*>		m_LoadedSprite;

			int							m_nRow;
			int							m_nColumns;
			int							m_nFrames;
			int							m_Index;
			D3DXIMAGE_INFO				m_Info;								// Information of image
			D3DXIMAGE_INFO				m_FrameInfo;						// Information of frame's image
			LPDIRECT3DTEXTURE9			m_Image;							//
			double						m_ElapedTime;
			D3DXVECTOR2					m_Scale;

			//Completed for other action
			bool						m_isCompleted;
			bool						m_isLoop;

			//Transform matrix
			D3DXMATRIX					m_CurrentMatrix;
			D3DXMATRIX					m_TransformMatrix;
			D3DXMATRIX					m_MultyMatrix;
};

#endif
