#include "Star.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Entity\Bonus\Brick.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"

inline bool IsCollision_Star(CMovable* entity, vector<CBaseEntity*> listEntity) {
	for (int i = 0; i < listEntity.size(); i++)
	{
		if (listEntity.at(i)->getTagNodeId() == TAGNODE::BRICK)
		{
			if (CCollision::CheckCollision(entity, listEntity.at(i)) == COLDIRECTION::COLDIRECTION_TOP)
			{
				return true;
			}
		}
	}

	return false;
}

CStar::CStar()
{
	this->initEntity();
}

CStar::CStar(vector3d pos)
{
	this->m_Position = pos;
	this->initEntity();
	this->STAR_POSITION_Y_MAX = pos.y + this->m_listSprite.at(0)->getFrameInfo().Height - ADD_POS_Y;
}

CStar:: ~CStar()
{
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CStar::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::STAR), 1, 4, 4, 0));
	return true;
}

bool CStar::initEntity()
{
	this->m_TagNode			= "Star";

	this->m_ResouceImage	= new CBonusResource();

	this->loadSprite();
	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	this->m_State			= 0;
	this->getBounding();

	this->m_Velocity		= vector2d(0, 0);
	return true;
}

void CStar::updateEntity(CKeyBoard* device)
{

}

void CStar::updateEntity(float deltaTime)
{
	if (this->m_Position.y >= STAR_POSITION_Y_MAX) {
		this->m_Velocity.y = VEL_DEFAULT_Y;
		this->m_Position.y = STAR_POSITION_Y_MAX;

		if (IsCollision_Star(this, CMapManager::getInstance()->getListBonus()))
		{
			this->m_Velocity.x = STAR_VELOCITY_MAX;
		}
		else
			this->m_Velocity.y = 0;

	}

	for (int i = 0; i < CMapManager::getInstance()->getListRect().size(); i++)
	{
		this->getBounding().setVelocity(this->getVelocity());
		if (CCollision::CheckCollision(this->getBounding(), *CMapManager::getInstance()->getListRect().at(i)) == COLDIRECTION::COLDIRECTION_TOP)
		{
			this->m_Velocity.y = VEL_DEFAULT_Y + BRICK_VELOCITY_MAX_Y;
		}
		else if (CCollision::CheckCollision(this->getBounding(), *CMapManager::getInstance()->getListRect().at(i)) == COLDIRECTION::COLDIRECTION_LEFT) {
			// Do something 
		}
	}

	this->m_Position = vector3d(this->m_Position.x + this->m_Velocity.x*deltaTime / 250, this->m_Position.y + (this->m_Velocity.y + GRAVITATION) *deltaTime / 100, 0);


	if (CCollision::CheckCollision(this, CPlayer::getInstance()))
	{
		if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::UNDYING ||
			CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::SMALL_UNDYING) {
			vector<CBaseEntity*> tempBonusList = CMapManager::getInstance()->getListBonusItem();
			CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::STAR);
			CMapManager::getInstance()->setListBonusItem(tempBonusList);
			tempBonusList.clear();
		}
	}
}

void CStar::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CStar::updateEntity(RECT* camera)
{

}

int	CStar::getTagNodeId(){
	return TAGNODE::STAR;
}

int CStar::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}