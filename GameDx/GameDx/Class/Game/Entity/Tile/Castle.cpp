#include "Castle.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"


CCastle::CCastle()
{
	this->initEntity();
}


CCastle:: ~CCastle()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

bool CCastle::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CASTTLE), 1, 1, 1, 0));
	return true;
}

bool CCastle::initEntity()
{
	m_Position				= vector3d(180, 110, 0);
	this->m_ResouceImage	= new CTileResource();
	this->loadSprite();
	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	m_TagNode				= "Castle";
	return true;
}

void CCastle::updateEntity(CKeyBoard* device)
{

}
void CCastle::updateEntity(float deltaTime)
{
	if (this->m_Position.y < 150)
	{
		m_Position = vector3d(150, 150, 0);
	}

}

void CCastle::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CCastle::updateEntity(RECT* camera)
{

}
