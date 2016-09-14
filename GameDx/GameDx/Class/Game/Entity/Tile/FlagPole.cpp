#include "FlagPole.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Utill\ShowBouding.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"

CFlagPole::CFlagPole()
{
	this->initEntity();
}

CFlagPole::CFlagPole(vector2d pos)
{
	this->m_Position.x		= pos.x;
	this->m_Position.y		= pos.y - 16;
	this->initEntity();

	this->getBounding();
}

CFlagPole:: ~CFlagPole()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

bool CFlagPole::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_FLAG_POLE), 1, 1, 1, 0));
	return true;
}

bool CFlagPole::initEntity()
{
	this->m_TagNode			= "FlagPole";

	this->m_State			= 0;
	this->m_ResouceImage	= new CTileResource();
	this->loadSprite();
	this->m_Bounding		= new CBox2D(0, 0, 0, 0);

	this->getBounding();

	return true;
}

void CFlagPole::updateEntity(CKeyBoard* device)
{
	
}

void CFlagPole::updateEntity(float deltaTime)
{
}

void CFlagPole::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
	{
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(1, 1), 0, DRAWCENTER_LEFT_BOTTOM, true, 10);
	}
}

void CFlagPole::updateEntity(RECT* camera)
{

}

int	CFlagPole::getTagNodeId() {
	return TAGNODE::FLAG_POLE;
}

int CFlagPole::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}