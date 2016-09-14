#include "Box2D.h"
#include "Class\Framework\Camera.h"

CBox2D::CBox2D()
{
	m_Position		= vector2dZero;
	m_Size			= vector2dZero;
	m_Velocity		= vector2dZero;
}

CBox2D::CBox2D(RECT rectangle)
{
	m_Position.x	= rectangle.left;
	m_Position.y	= rectangle.top;

	m_Size.x		= rectangle.right	- rectangle.left;
	m_Size.y		= rectangle.top		- rectangle.bottom;

	m_Velocity		= vector2dZero;
}

CBox2D::CBox2D(RECT rectangle, vector2d velocity)
{
	m_Position.x	= rectangle.left;
	m_Position.y	= rectangle.top;

	m_Size.x		= rectangle.right	- rectangle.left;
	m_Size.y		= rectangle.top		- rectangle.bottom;

	m_Velocity		= velocity;
}

CBox2D::CBox2D(float x, float y, float width, float height)
{
	m_Position.x	= x;
	m_Position.y	= y;

	m_Size.x		= width;
	m_Size.y		= height;

	m_Velocity		= vector2dZero;
}

CBox2D::CBox2D(float x, float y, float width, float height, vector2d velocity)
{
	m_Position.x = x;
	m_Position.y = y;

	m_Size.x = width;
	m_Size.y = height;

	m_Velocity = velocity;
}


CBox2D::CBox2D(LPDIRECT3DDEVICE9 device, RECT rectangle, vector2d velocity)
{

	HRESULT hr = D3DXCreateLine(device, &m_line);

	if (FALSE(hr))
		return;

	m_Position.x	= rectangle.left;
	m_Position.y	= rectangle.top;

	m_Size.x		= rectangle.right	- rectangle.left	+ deltaBoundingBox.x*2;
	m_Size.y		= rectangle.top		- rectangle.bottom	+ deltaBoundingBox.y*2;

	m_Velocity		= velocity;
}

CBox2D::CBox2D(LPDIRECT3DDEVICE9 device, vector2d pos, vector2d size, vector2d velocity)
{

	HRESULT hr = D3DXCreateLine(device, &m_line);

	if (FALSE(hr))
		return;

	m_Position = pos;

	m_Size.x = size.x + deltaBoundingBox.x * 2;
	m_Size.y = size.y + deltaBoundingBox.y * 2;

	m_Velocity = velocity;
}

CBox2D::~CBox2D()
{
}

void	CBox2D::update(float deltaTime, vector2d positionEntity)
{
	m_Position = positionEntity;
	m_Position.x -= deltaBoundingBox.x;
	m_Position.y += deltaBoundingBox.y;
	// viet swept AABB vo day
}

void	CBox2D::render()
{
	vector2d	vertex1[] = { CCamera::setPositionEntity(vector3d(m_Position)), CCamera::setPositionEntity(vector3d(vector2d(m_Position.x, m_Position.y - m_Size.y))) };
	m_line->Draw(vertex1, 2, 0xFFFF00FF);

	vector2d	vertex2[] = { CCamera::setPositionEntity(vector3d(vector2d(m_Position.x, m_Position.y - m_Size.y))), CCamera::setPositionEntity(vector3d(vector2d(m_Position.x + m_Size.x, m_Position.y - m_Size.y))) };
	m_line->Draw(vertex2, 2, 0xFFFF00FF);

	vector2d	vertex3[] = { CCamera::setPositionEntity(vector3d(vector2d(m_Position.x + m_Size.x, m_Position.y - m_Size.y))), CCamera::setPositionEntity(vector3d(vector2d(m_Position.x + m_Size.x, m_Position.y))) };
	m_line->Draw(vertex3, 2, 0xFFFF00FF);

	vector2d	vertex4[] = { CCamera::setPositionEntity(vector3d(m_Position)), CCamera::setPositionEntity(vector3d(vector2d(m_Position.x + m_Size.x, m_Position.y))) };
	m_line->Draw(vertex4, 2, 0xFFFF00FF);
}

float	CBox2D::getHeight()
{
	return m_Size.y;
}

void	CBox2D::setHeight(float param1)
{
	m_Size.y = param1;
}

float	CBox2D::getWidth()
{
	return m_Size.x;
}

void	CBox2D::setWidth(float param1)
{
	m_Size.x = param1;
}

float	CBox2D::getX()
{
	return m_Position.x;
}

void	CBox2D::setX(float param1)
{
	m_Position.x = param1;
}

float	CBox2D::getY()
{
	return m_Position.y;
}

void	CBox2D::setY(float param1)
{
	m_Position.y = param1;
}

float	CBox2D::getVelocityX()
{
	return m_Velocity.x;
}

void	CBox2D::setVelocityX(float param1)
{
	m_Velocity.x = param1;
}

float	CBox2D::getVelocityY()
{
	return m_Velocity.y;
}

vector2d CBox2D::getVelocity(){
	return m_Velocity;
}

void CBox2D::setVelocityY(float param1)
{
	m_Velocity.y = param1;
}

void CBox2D::setVelocity(vector2d newVel){
	m_Velocity.x = newVel.x;
	m_Velocity.y = newVel.y;
}

bool CBox2D::Intersect(CBox2D box1, CBox2D box2)
{
	return !(
			box1.getX()									> (box2.getX() + box2.getWidth())	||
			(box1.getWidth()	+ box1.getX()			< box2.getX())						||
			(box1.getY()		- box1.getHeight()		> box2.getY())						||
			(box1.getY()								< box2.getY() - box2.getHeight())
			);
}