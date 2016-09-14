#include "StaticEntity.h"


CStaticEntity::CStaticEntity()
{
	this->initEntity();
}


CStaticEntity::~CStaticEntity()
{
}

bool CStaticEntity::initEntity()
{
	m_TagNode = "Static";
	m_State = 0;
	return true;
}

CBox2D  CStaticEntity::getBounding()
{
	if (m_listSprite.size())
	{
		m_Bounding->setX(m_Position.x - m_listSprite.at(m_State)->getFrameInfo().Width / 2 * std::abs(m_listSprite.at(m_State)->getScale().x));
		m_Bounding->setY(m_Position.y + m_listSprite.at(m_State)->getFrameInfo().Height / 2 * std::abs(m_listSprite.at(m_State)->getScale().y));
		m_Bounding->setWidth(m_listSprite.at(m_State)->getFrameInfo().Width        * std::abs(m_listSprite.at(m_State)->getScale().x));
		m_Bounding->setHeight(m_listSprite.at(m_State)->getFrameInfo().Height      * std::abs(m_listSprite.at(m_State)->getScale().y));
	}
	return *m_Bounding;
}

//CBox2D  CStaticEntity::getBounding()
//{
// if (m_listSprite.size())
// {
//  m_Bounding->setX(m_Position.x);
//  m_Bounding->setY(m_Position.y);
//  m_Bounding->setWidth(m_listSprite.at(m_State)->getFrameInfo().Width        * std::abs(m_listSprite.at(m_State)->getScale().x));
//  m_Bounding->setHeight(m_listSprite.at(m_State)->getFrameInfo().Height      * std::abs(m_listSprite.at(m_State)->getScale().y));
// }
// return *m_Bounding;
//}

vector3d CStaticEntity::getPosition()
{
	return m_Position;
}

const char* CStaticEntity::getTagNode()
{
	return this->m_TagNode;
}

vector2d CStaticEntity::getVelocity()
{
	return m_Velocity;
}