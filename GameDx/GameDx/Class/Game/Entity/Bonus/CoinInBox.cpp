#include "CoinInBox.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"
#include "Class\Game\Scene\PopupInfo.h"

CCoinInBox::CCoinInBox()
{
	this->initEntity();
}

CCoinInBox::CCoinInBox(vector3d pos)
{
	this->m_Position	= pos;
	this->initEntity();
	this->m_Pos_y_Max	= this->m_Position.y + 2* this->m_listSprite.at(0)->getFrameInfo().Height;
	this->m_Pos_y_Min	= this->m_Position.y + this->m_listSprite.at(0)->getFrameInfo().Height;
}

CCoinInBox:: ~CCoinInBox()
{
	SAFE_RELEASE(this->m_Sound);
	SAFE_RELEASE(this->m_ResouceImage);
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CCoinInBox::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::COININBOX), 1, 4, 4, 0));
	return true;
}

bool CCoinInBox::initEntity()
{
	this->m_TagNode			= "CoinInBox";
	this->m_ResouceImage	= new CBonusResource();
	this->loadSprite();
	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	this->m_State			= 0;
	this->getBounding();
	this->m_Velocity		= vector2d(0, 0);

//	m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_coin.wav");
	return true;
}

void CCoinInBox::updateEntity(CKeyBoard* device)
{

}

void CCoinInBox::updateEntity(float deltaTime)
{
//	CAudio::getInstance()->PlaySoundW(m_Sound);
	// Handle: Player day cuc gach an tien lien tuc

	vector<CBaseEntity*> ListBonusItem = CMapManager::getInstance()->getListBonusItem();
	for (int i = 0; i < ListBonusItem.size(); ++i) {
		if (ListBonusItem.at(i)->getTagNodeId() == TAGNODE::COININBOX &&
			ListBonusItem.at(i)->getPosition().y <= m_Pos_y_Min &&
			ListBonusItem.at(i)->getVelocity().y <= 0)
		{
			CPopUpInfo::getInstance()->addPoint(1);
			CPopUpInfo::getInstance()->addCoin(1);

			vector<CBaseEntity*> tempBonusList = ListBonusItem;
			CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::COININBOX);
			CMapManager::getInstance()->setListBonusItem(tempBonusList);
			tempBonusList.clear();
		}
	}

	if (this->m_Position.y >= this->m_Pos_y_Max)
	{
		m_Velocity.y = CHANGE_DIRECTION(m_Velocity.y);
	}
	if (this->m_Position.y <= this->m_Pos_y_Min && (this->m_Velocity.y + GRAVITATION) <= 0)
	{
		m_Velocity.y = VEL_DEFAULT_Y;

		/*CPopUpInfo::getInstance()->addPoint(1);
		CPopUpInfo::getInstance()->addCoin(1);*/

		vector<CBaseEntity*> tempBonusList = ListBonusItem;
		CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::COININBOX);
		CMapManager::getInstance()->setListBonusItem(tempBonusList);
		tempBonusList.clear();
	}
	this->m_Position.y = this->m_Position.y + (this->m_Velocity.y + SIGN(m_Velocity.y) * GRAVITATION) *deltaTime / 100;
}

void CCoinInBox::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CCoinInBox::updateEntity(RECT* camera)
{

}

int	CCoinInBox::getTagNodeId()
{
	return TAGNODE::COININBOX;
}

int CCoinInBox::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}