#include "Coin.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Scene\PopupInfo.h"

CCoin::CCoin()
{
	this->initEntity();
}

CCoin::CCoin(vector2d newPosition)
{
	m_Position.x	= newPosition.x;
	m_Position.y	= newPosition.y;

	m_State			= 0;

	this->initEntity();
}


CCoin:: ~CCoin()
{
	SAFE_RELEASE(this->m_ResouceImage);
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CCoin::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::COIN), 1, 4, 4, 0));
	return true;
}

bool CCoin::initEntity()
{
	this->m_ResouceImage	= new CBonusResource();
	this->loadSprite();

	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	this->getBounding();
	
	return true;
}

void CCoin::updateEntity(CKeyBoard* device)
{

}

void CCoin::updateEntity(float deltaTime)
{
	if (CCollision::CheckCollision(CPlayer::getInstance(), this))
	{
		this->isDestroy = true;

		CPopUpInfo::getInstance()->addPoint(1);
		CPopUpInfo::getInstance()->addCoin(1);

		vector<CBaseEntity*> tempBonusList = CMapManager::getInstance()->getListBonus();
		CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::COIN);
		CMapManager::getInstance()->setListBonus(tempBonusList);
		tempBonusList.clear();
	}
}

void CCoin::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CCoin::updateEntity(RECT* camera)
{

}

int  CCoin::getTagNodeId()
{
	return TAGNODE::COIN;
}

int CCoin::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}