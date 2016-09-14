#include "FlagPoleTail.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"

CFlagPoleTail::CFlagPoleTail()
{
	this->initEntity();
}

CFlagPoleTail::CFlagPoleTail(vector2d pos)
{
	this->m_Position.x = pos.x;
	this->m_Position.y = pos.y;
	this->initEntity();

	this->getBounding();
}

CFlagPoleTail:: ~CFlagPoleTail()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

bool CFlagPoleTail::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_FLAG_POLE_TAIL), 1, 1, 1, 0));
	return true;
}

bool CFlagPoleTail::initEntity()
{
	this->m_TagNode				= "FlagPoleTail";
	this->m_State				= 0;

	this->m_ResouceImage		= new CTileResource();
	this->loadSprite();

	this->m_Bounding			= new CBox2D(0, 0, 0, 0);
	this->getBounding();

	return true;
}

void CFlagPoleTail::updateEntity(CKeyBoard* device)
{

}
void CFlagPoleTail::updateEntity(float deltaTime)
{
}
void CFlagPoleTail::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(1, 1), 0, DRAWCENTER_LEFT_TOP, true, 10);
}

void CFlagPoleTail::updateEntity(RECT* camera)
{

}

int	CFlagPoleTail::getTagNodeId() {
	return TAGNODE::FLAG_POLE_TAIL;
}

int CFlagPoleTail::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}