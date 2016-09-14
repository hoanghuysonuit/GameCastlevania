#include "RedMushroom.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"

CRedMushroom::CRedMushroom()
{
	this->initEntity();
}

CRedMushroom:: ~CRedMushroom()
{

}

bool CRedMushroom::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(CInfomationResource::redmushroom, 1, 1, 1, 0));
	return true;
}

bool CRedMushroom::initEntity()
{
	m_Position = vector3d(50, 160, 0);
	this->loadSprite();
	this->m_Bounding = new CBox2D(0, 0, 0, 0);
	this->m_Velocity = vector2d(9.8, 9.8);
	return true;
}

void CRedMushroom::updateEntity(CKeyBoard* device)
{

}

void CRedMushroom::updateEntity(float deltaTime)
{
}

void CRedMushroom::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CRedMushroom::updateEntity(RECT* camera)
{

}

void CRedMushroom::setVelocity(vector2d velocity)
{
	this->m_Velocity.x = velocity.x;
	this->m_Velocity.y = velocity.y;
}

int	CRedMushroom::getTagNodeId(){
	return TAGNODE::RED_MUSHROOM;
}

