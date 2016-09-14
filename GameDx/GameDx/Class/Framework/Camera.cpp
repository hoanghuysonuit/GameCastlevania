
#include "Camera.h"
#include "Class\Game\Scene\PopupInfo.h"
#include "Class\Game\Entity\Map\MapManager.h"

vector3d			CCamera::m_Position					= vector3dZero;
matrix				CCamera::m_MatrixTransform;
vector4d			CCamera::m_Viewport;
float*				CCamera::m_ViewportX				= 0;
float*				CCamera::m_ViewportY				= 0;
RECT				CCamera::m_LimitRect				= RECT();
CCamera*			CCamera::m_Instance					= NULL;
CAMERASTATE			CCamera::m_StateCamera				= CAMERASTATE::CAMERA_NORMAL;

CCamera::CCamera()
{
	m_Position		= vector3d(0, BACKBUFFER_HEIGHT, 0);
	m_ViewportX		= &m_Position.x;
	m_ViewportY		= &m_Position.y;
	setLimitRectOfCurrentMap(CMapManager::getInstance()->getListMapInGame().at(CMapManager::getInstance()->getCurrentMapINT())->m_sizeX, 
		CMapManager::getInstance()->getListMapInGame().at(CMapManager::getInstance()->getCurrentMapINT())->m_sizeY);
	D3DXMatrixIdentity(&m_MatrixTransform);
	
}


CCamera::~CCamera()
{
	SAFE_RELEASE(m_ViewportX);
	SAFE_RELEASE(m_ViewportY);
	SAFE_RELEASE(m_Instance);
}

CCamera*	CCamera::getInstance()
{
	if (!m_Instance)
		m_Instance	= new CCamera();
	return	m_Instance;
}

void		CCamera::setLimitRect(RECT newSizeWorld){
	m_LimitRect = newSizeWorld;
}

CAMERASTATE	CCamera::getStateCamera()
{
	return m_StateCamera;
}

void		CCamera::setPositionCamera(vector3d newPos)
{
	m_Position.x = newPos.x;
	m_Position.y = newPos.y;
}

vector3d	CCamera::getPosisionCamera()
{
	return m_Position;
}

vector4d	CCamera::getViewport()
{
	return m_Viewport;
}

CBox2D		CCamera::getBoundingScreen()
{
	return CBox2D(m_Position.x, m_Position.y, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
}

void CCamera::Update(vector3d	positionEntity)
{
	switch (CCamera::getInstance()->getStateCamera())
	{
	case CAMERA_NORMAL:
		NormalUpdate(positionEntity);
		break;
	case CAMERA_AUTO:
		AutoUpdate(positionEntity);
		break;
	case CAMERA_STOP:
		break;
	default:
		break;
	}
}

void	CCamera::NormalUpdate(vector3d	positionEntity)
{
	if (positionEntity.x - BACKBUFFER_WIDTH / 2.0f > m_LimitRect.left - 16
		&& positionEntity.x + BACKBUFFER_WIDTH < m_LimitRect.right)
		m_Position.x = positionEntity.x - BACKBUFFER_WIDTH / 2.0f;

	m_MatrixTransform._22 = -1.0f;
	m_MatrixTransform._41 = -*m_ViewportX;
	m_MatrixTransform._42 = m_Position.y;
}

void	CCamera::AutoUpdate(vector3d positionEntiyt)
{

}

vector3d	CCamera::setPositionEntity(vector3d	&pos)
{
	if (!m_Instance)
		m_Instance = new CCamera();
	D3DXVec3Transform(&m_Viewport, &pos, &m_MatrixTransform);
	return D3DXVECTOR3(m_Viewport.x, m_Viewport.y, 0);
}

void		CCamera::setLimitRectOfCurrentMap(float width, float height)
{
	this->m_LimitRect.left			= 0;
	this->m_LimitRect.right			= this->m_LimitRect.left + width - BACKBUFFER_HEIGHT/2;
	this->m_LimitRect.bottom		= 240;
	this->m_LimitRect.top			= this->m_LimitRect.bottom + height;
}