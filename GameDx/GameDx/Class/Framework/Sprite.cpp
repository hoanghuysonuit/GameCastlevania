#include "Sprite.h"

LPD3DXSPRITE		CSprite::m_spriteHandler	= NULL;
LPDIRECT3DDEVICE9	CSprite::m_d3dDevice		= 0;
vector<CSprite*>	CSprite::m_LoadedSprite;


CSprite::CSprite(wstring filePath, int nRows, int nColumns, int nFrame, int Index)
{
	this->m_Image					= NULL;
	this->m_nColumns				= nColumns;
	this->m_nRow					= nRows;
	this->m_nFrames					= nFrame;
	this->m_Index					= Index;
	this->m_ElapedTime				= 0.0;
	this->m_Scale					= vector2d(1, 1);
	
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(filePath.c_str(), &this->m_Info);
	if (hr != D3D_OK)
		return;
	
	hr = D3DXCreateTextureFromFileEx(
										m_d3dDevice,
										filePath.c_str(),
										m_Info.Width,
										m_Info.Height,
										1,
										D3DUSAGE_DYNAMIC,
										D3DFMT_UNKNOWN,
										D3DPOOL_DEFAULT,
										D3DX_DEFAULT,
										D3DX_DEFAULT,
										D3DCOLOR_XRGB(34, 177, 76),
										&m_Info,
										NULL,
										&m_Image
									);
	if (hr != D3D_OK)		
		return;

	this->m_FrameInfo.Width		= (int)((float)this->m_Info.Width  / (float)this->m_nColumns);
	this->m_FrameInfo.Height	= (int)((float)this->m_Info.Height / (float)this->m_nRow);
	this->m_isCompleted = false;

}

CSprite::CSprite(const CSprite& source){
}

CSprite::~CSprite()
{
	if (this->m_LoadedSprite.empty())
	{
		m_LoadedSprite.clear();
		m_LoadedSprite.~vector();
	}
}

bool		CSprite::Render(D3DXVECTOR3 position, D3DXVECTOR2 scale, float rotate, int drawcenter, bool isLoop, float FPSs, D3DCOLOR anphaBlend)
{
	// get frame's size (frame is a image which's part of sprite, sprite is a big image which include many small images and describe state of character)
	RECT rec;
	rec				= getScrRect();
	m_isCompleted	= false;
	this->m_Scale	= scale;

	// center point to draw
	D3DXVECTOR3 center = this->setCenter(drawcenter);

	// position
	position.x = (int)position.x;
	position.y = (int)position.y;
	position.z = (int)position.z;

	// transform: rotate, flip, scale...
	m_spriteHandler->GetTransform(&m_CurrentMatrix);
	D3DXMatrixTransformation2D(&m_TransformMatrix, &(D3DXVECTOR2)position, 0, &m_Scale, &(D3DXVECTOR2)position, D3DXToRadian(rotate), NULL);
	D3DXMatrixMultiply(&m_MultyMatrix, &m_TransformMatrix, &m_CurrentMatrix);
	m_spriteHandler->SetTransform(&m_MultyMatrix);

	// draw sprite into the screen
	m_spriteHandler->Draw(
		m_Image,
		&rec,
		&center,
		&position,
		anphaBlend
		);

	m_spriteHandler->SetTransform(&m_CurrentMatrix);

	// FPSs (FPS of Sprite). FPS is how many frames whoch are drawn in 1 second (1000 millisecond)
	// So if time to draw of game (this's time of a render or update loop) is smaller than time we want we have to sleep.
	// However, if sleep chaging frame isn't really good, good way is redraw the previous frame. That's mean no change index.
	// if time is enough to draw, we increase index by calling Next function and change value of elapedTime.
	if (double(FPSs)*m_ElapedTime >= 1000.0f)
	{
		this->m_isLoop = isLoop;
		Next();
		m_ElapedTime	= 0.0;
		

		// know drawing completly or not yet. if action is repeated , index equal 0; if not draw the last frame (That's mean action isn't repeated)
		m_isCompleted	= isCompleted(m_nColumns*m_nRow);	
	}

	// special thing. stupid code
	if (CTimer::getInstance()->getElapedTime() < 0)
		return false;

	// if time to draw in real is smaller than time to set, we skip increase index and sum time of this loop.
	m_ElapedTime		+= CTimer::getInstance()->getElapedTime();

	return m_isCompleted;
}
bool		CSprite::Render(int fromFrame, int toFrame, D3DXVECTOR3 position, D3DXVECTOR2 scale, float rotate, int drawcenter, bool isLoop, float FPSs, D3DCOLOR anphaBlend)
{
	if (this->m_Index <= fromFrame)
		m_Index = fromFrame;
	if (this->m_Index >= toFrame)
		m_Index = toFrame;

	// get frame's size (frame is a image which's part of sprite, sprite is a big image which include many small images and describe state of character)
	RECT rec;
	rec				= getScrRect();
	m_isCompleted	= false;
	this->m_Scale	= scale;

	// center point to draw
	D3DXVECTOR3 center = this->setCenter(drawcenter);

	// position
	position.x = (int)position.x;
	position.y = (int)position.y;
	position.z = (int)position.z;

	// transform: rotate, flip, scale...
	m_spriteHandler->GetTransform(&m_CurrentMatrix);
	D3DXMatrixTransformation2D(&m_TransformMatrix, &(D3DXVECTOR2)position, 0, &m_Scale, &(D3DXVECTOR2)position, D3DXToRadian(rotate), NULL);
	D3DXMatrixMultiply(&m_MultyMatrix, &m_TransformMatrix, &m_CurrentMatrix);
	m_spriteHandler->SetTransform(&m_MultyMatrix);

	// draw sprite into the screen
	m_spriteHandler->Draw(
		m_Image,
		&rec,
		&center,
		&position,
		anphaBlend
		);

	m_spriteHandler->SetTransform(&m_CurrentMatrix);

	// FPSs (FPS of Sprite). FPS is how many frames whoch are drawn in 1 second (1000 millisecond)
	// So if time to draw of game (this's time of a render or update loop) is smaller than time we want we have to sleep.
	// However, if sleep chaging frame isn't really good, good way is redraw the previous frame. That's mean no change index.
	// if time is enough to draw, we increase index by calling Next function and change value of elapedTime.
	if (double(FPSs)*m_ElapedTime >= 1000.0f)
	{
		this->m_isLoop = isLoop;
		Next();
		m_ElapedTime = 0.0;

		// know drawing completly or not yet. if action is repeated , index equal 0; if not draw the last frame (That's mean action isn't repeated)
		m_isCompleted = isCompleted(toFrame);
	}
	// special thing. stupid code
	if (CTimer::getInstance()->getElapedTime() < 0)
		return false;

	// if time to draw in real is smaller than time to set, we skip increase index and sum time of this loop.
	m_ElapedTime += CTimer::getInstance()->getElapedTime();

	return m_isCompleted;
}
RECT		CSprite::getScrRect()
{
	RECT rect;
	rect.left		= (UINT)m_FrameInfo.Width  * (m_Index - (int)(m_Index / m_nColumns) * m_nColumns);
	rect.top		= (UINT)m_FrameInfo.Height * (int)(m_Index / m_nColumns);
	rect.right		= rect.left + (UINT)m_FrameInfo.Width;
	rect.bottom		= rect.top + (UINT)m_FrameInfo.Height;
	return rect;
}

D3DXVECTOR3	CSprite::setCenter(int drawcenter)
{
	D3DXVECTOR3 result;
	switch (drawcenter)
	{
	case DRAWCENTER_LEFT_TOP:
		result.x = 0;
		result.y = 0;
		break;
	case DRAWCENTER_LEFT_MIDDLE:
		result.x = 0;
		result.y = this->m_FrameInfo.Height / 2.0f;
		break;
	case DRAWCENTER_LEFT_BOTTOM:
		result.x = 0;
		result.y = this->m_FrameInfo.Height;
		break;
	case DRAWCENTER_MIDDLE_TOP:
		result.x = this->m_FrameInfo.Width / 2.0f;
		result.y = 0;
		break;
	case DRAWCENTER_MIDDLE_MIDDLE:
		result.x = this->m_FrameInfo.Width / 2.0f;
		result.y = this->m_FrameInfo.Height / 2.0f;
		break;
	case DRAWCENTER_MIDDLE_BOTTOM:
		result.x = this->m_FrameInfo.Width / 2.0f;
		result.y = this->m_FrameInfo.Height;
		break;
	case DRAWCENTER_RIGHT_TOP:
		result.x = this->m_FrameInfo.Width;
		result.y = 0;
		break;
	case DRAWCENTER_RIGHT_MIDDLE:
		result.x = this->m_FrameInfo.Width;
		result.y = this->m_FrameInfo.Height / 2.0f;
		break;
	case DRAWCENTER_RIGHT_BOTTOM:
		result.x = this->m_FrameInfo.Width;
		result.y = this->m_FrameInfo.Height;
		break;
	default:
		break;
	}
	result.z = 0;
	return result;
}

void		CSprite::Next() 
{
	m_Index++;
}

void		CSprite::Reset() 
{
	m_Index = 0;
	m_isCompleted = false;
}

int			CSprite::getIndex()
{
	return m_Index;
}

bool		CSprite::isCompleted(int toFrame) 
{	
	if (m_Index >= toFrame)
	{
		if (this->m_isLoop)
			Reset();
		else
			m_Index = toFrame;
		return true;
	}
	return false;
}

void		CSprite::initSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	m_spriteHandler = spriteHandler;
	m_spriteHandler->GetDevice(&m_d3dDevice);
}

D3DXIMAGE_INFO	CSprite::getFrameInfo()
{
	return this->m_FrameInfo;
}

D3DXVECTOR2		CSprite::getScale()
{
	return this->m_Scale;
}