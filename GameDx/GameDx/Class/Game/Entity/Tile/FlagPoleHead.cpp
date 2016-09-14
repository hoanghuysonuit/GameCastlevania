#include "FlagPoleHead.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"

CFlagPoleHead::CFlagPoleHead()
{
	this->initEntity();
}

CFlagPoleHead:: ~CFlagPoleHead()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

CFlagPoleHead::CFlagPoleHead(vector2d pos)
{
	this->m_Position.x = pos.x;
	this->m_Position.y = pos.y - 16;
	this->initEntity();

	this->getBounding();
}
bool CFlagPoleHead::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_FLAG_POLE_HEAD), 1, 1, 1, 0));
	return true;
}

bool CFlagPoleHead::initEntity()
{
	this->m_TagNode				= "FlagPoleHead";
	this->m_State				= 0;

	this->m_ResouceImage		= new CTileResource();
	this->loadSprite();

	this->m_Bounding			= new CBox2D(0, 0, 0, 0);
	this->getBounding();

	return true;
}

void CFlagPoleHead::updateEntity(CKeyBoard* device)
{

}

void CFlagPoleHead::updateEntity(float deltaTime)
{
}

void CFlagPoleHead::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_LEFT_TOP, true, 10);
}

void CFlagPoleHead::updateEntity(RECT* camera)
{

}

