#include "Iteminbox.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"

inline bool IsCollision(CMovable* entity, vector<CBaseEntity*> listEntity) {
	for (int i = 0; i < listEntity.size(); i++)
	{
		if (listEntity.at(i)->getTagNodeId() == TAGNODE::GIFT_BOX)
		{
			if (CCollision::CheckCollision(entity, listEntity.at(i)) == COLDIRECTION::COLDIRECTION_TOP)
			{
				return true;
			}
		}
	}

	return false;
}

inline bool getCollisionHandle(CMovable* entity) {
	for (int i = 0; i < CMapManager::getInstance()->getListRect().size(); i++)
	{
		entity->getBounding().setVelocity(entity->getVelocity());
		if (CCollision::CheckCollision(entity->getBounding(), *(CMapManager::getInstance()->getListRect().at(i))))
		{
			return true;
		}
	}

	return false;
}

CIteminbox::CIteminbox()
{
	this->initEntity();
}

CIteminbox::CIteminbox(vector2d pos)
{
	this->m_Position.x		= pos.x;
	this->m_Position.y		= pos.y;
	this->initEntity();

	this->ITEMINBOX_POSITION_Y_MAX = pos.y + this->m_listSprite.at(this->m_itemtype)->getFrameInfo().Height - ADD_POS_Y;
}

CIteminbox:: ~CIteminbox()
{
	SAFE_RELEASE(this->m_Sound1);
	SAFE_RELEASE(this->m_Sound2);
	SAFE_RELEASE(this->m_ResouceImage);
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CIteminbox::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::RED_MUSHROOM), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::FLOWER), 1, 4, 4, 0));
	return true;
}

bool CIteminbox::initEntity()
{
	chkShowItem(CPlayer::getInstance());
	this->m_ResouceImage		= new CBonusResource();
	this->loadSprite();

	this->m_Bounding			= new CBox2D(0, 0, 0, 0);
	this->m_State				= 0;
	this->getBounding();

	/*if (this->m_itemtype == ITEMINBOX_TYPE::REDMUSHROOM)
	{
	this->m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_powerup_appears.wav");
	}
	else if (this->m_itemtype == ITEMINBOX_TYPE::ITEM_FLOWER)
	{
	this->m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_powerup_appears.wav");
	}*/
	this->m_Sound1 = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_powerup_appears.wav");
	this->m_Sound2 = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_powerup.wav");
	return true;
}

void CIteminbox::updateEntity(CKeyBoard* device)
{

}

void CIteminbox::updateEntity(float deltaTime)
{
	//	CAudio::getInstance()->PlaySoundW(this->m_Sound1);
	if (this->m_itemtype == ITEMINBOX_TYPE::REDMUSHROOM)
	{
		if (this->m_Position.y >= ITEMINBOX_POSITION_Y_MAX)
		{
			this->m_Velocity.y = VEL_DEFAULT_Y;
			this->m_Position.y = ITEMINBOX_POSITION_Y_MAX;

			if (IsCollision(this, CMapManager::getInstance()->getListBonus()))
			{
				this->m_Velocity.x = REDMUSHROOM_VELOCITY_MAX;
			}
			else{
				this->m_Velocity.y = 0;
			}
		}
		if (getCollisionHandle(this)) {

			vector<CBox2D*> listRect = CMapManager::getInstance()->getListRect();
			for (int i = 0; i < listRect.size(); i++)
			{
				this->getBounding().setVelocity(this->getVelocity());

				if (CCollision::CheckCollision(this->getBounding(), *listRect.at(i)) == COLDIRECTION::COLDIRECTION_TOP)
				{
					this->m_Position.y = listRect.at(i)->getY() + this->m_Bounding->getHeight() / 2;
					this->m_Velocity.y = VEL_DEFAULT_Y;
				}
				else if (CCollision::CheckCollision(this->getBounding(), *listRect.at(i)) == COLDIRECTION::COLDIRECTION_LEFT) {
					// Change direction 
					if (m_Velocity.x >= 0)
						this->m_Velocity.x = -(this->m_Velocity.x = VEL_DEFAULT_X + REDMUSHROOM_VELOCITY_MAX);
				}
				else if (CCollision::CheckCollision(this->getBounding(), *listRect.at(i)) == COLDIRECTION::COLDIRECTION_NONE)
				{
					/*if (this->getVelocity().x != VEL_DEFAULT_X &&
						IsCollision(this, CMapManager::getInstance()->getListBonus()) == false)
						this->m_Velocity.y = 0;*/
				}
			}

			listRect.clear();
		}

		this->m_Position = vector3d(this->m_Position.x + this->m_Velocity.x*deltaTime / 250, this->m_Position.y + (this->m_Velocity.y + GRAVITATION) *deltaTime / 100, 0);

		if (CCollision::CheckCollision(this, CPlayer::getInstance()))
		{
			if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::BIG)
			{
				/*CAudio::getInstance()->StopSound(this->m_Sound1);
				CAudio::getInstance()->PlaySoundW(this->m_Sound2);*/
				vector<CBaseEntity*> tempBonusList = CMapManager::getInstance()->getListBonusItem();
				CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::RED_MUSHROOM);
				CMapManager::getInstance()->setListBonusItem(tempBonusList);
				tempBonusList.clear();
			}
		}
	}
	else if (this->m_itemtype == ITEMINBOX_TYPE::ITEM_FLOWER)
	{
		if (this->m_Position.y > ITEMINBOX_POSITION_Y_MAX) {
			this->m_Velocity.y = VEL_DEFAULT_Y;
			this->m_Position.y = ITEMINBOX_POSITION_Y_MAX;
		}
		this->m_Position = vector3d(this->m_Position.x + this->m_Velocity.x*deltaTime / 250, this->m_Position.y + (this->m_Velocity.y + GRAVITATION) *deltaTime / 100, 0);

		if (CCollision::CheckCollision(this, CPlayer::getInstance()))
		{
			/*CAudio::getInstance()->StopSound(this->m_Sound1);
			CAudio::getInstance()->PlaySoundW(this->m_Sound2);*/

			if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::FIRE)
			{
				vector<CBaseEntity*> tempBonusList = CMapManager::getInstance()->getListBonusItem();
				CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::FLOWER);
				CMapManager::getInstance()->setListBonusItem(tempBonusList);
				tempBonusList.clear();
			}
		}
	}
}

void CIteminbox::drawEntity()
{
	this->m_listSprite.at(this->m_itemtype)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CIteminbox::updateEntity(RECT* camera)
{

}

void CIteminbox::setVelocity(vector2d velocity)
{
	this->m_Velocity.x = velocity.x;
	this->m_Velocity.y = velocity.y;
}

void CIteminbox::setPosition(vector3d position)
{
	this->m_Position = position;
}

ITEMINBOX_TYPE CIteminbox::getItemType()
{
	return this->m_itemtype;
}

void CIteminbox::chkShowItem(CPlayer* player)
{
	if (player->getPlayerTag() == PLAYERTAGS::SMALL)
	{
		this->m_itemtype = ITEMINBOX_TYPE::REDMUSHROOM;
		this->m_TagNode = "RedMushroom";
	}
	if (player->getPlayerTag() == PLAYERTAGS::BIG)
	{
		this->m_itemtype = ITEMINBOX_TYPE::ITEM_FLOWER;
		this->m_TagNode = "Flower";
	}
}

int  CIteminbox::getTagNodeId()
{
	if (this->m_itemtype == ITEMINBOX_TYPE::REDMUSHROOM)
	{
		return TAGNODE::RED_MUSHROOM;
	}
	else if (this->m_itemtype == ITEMINBOX_TYPE::ITEM_FLOWER)
	{
		return TAGNODE::FLOWER;
	}
}

int CIteminbox::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}