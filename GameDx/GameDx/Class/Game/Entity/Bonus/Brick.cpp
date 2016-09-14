#include "Brick.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\Bonus\CoinInBox.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"
#include "Class\Game\Scene\PopupInfo.h"

inline int getIndex(vector<CBaseEntity*> list, CBaseEntity* entity) {
	for (int i = 0; i < list.size(); ++i) {
		if (CMapManager::getInstance()->getListBonus().at(i) == entity) {
			return i;
		}
	}
}

CBrick::CBrick()
{
	m_BrickType = BRICK_TYPE::BRICK_NONE;
	this->initEntity();
}

CBrick::CBrick(int map, vector2d position, BRICK_TYPE type)
{
	this->map			= map;
	this->PrePos		= vector3d(position.x, position.y, 0);

	this->m_Position.x	= position.x;
	this->m_Position.y	= position.y;

	this->m_Bounding	= new CBox2D(0, 0, 0, 0);

	this->m_Velocity	= vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y);
	m_BrickType			= type;

	this->initEntity();
}

CBrick:: ~CBrick()
{
	SAFE_RELEASE(m_Coin);
	SAFE_RELEASE(m_Star);
	SAFE_RELEASE(m_GreenMushRoom);
	for (int i = 0; i < m_BrickMini.size(); i++){
		SAFE_RELEASE(m_BrickMini.at(i));
	}
	SAFE_RELEASE(this->m_ResouceImage);

	for (int i = 0; i < m_BrickMini.size(); ++i) {
		SAFE_RELEASE(m_BrickMini.at(i));
		m_BrickMini.at(i) = nullptr;
	}

	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CBrick::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICK, BRICK_STATE::BRICK_BOX), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICK, BRICK_STATE::BRICK_NORMAL), 1, 1, 1, 0));

	return true;
}

bool CBrick::initEntity()
{
	m_Star					= nullptr;
	m_Coin					= nullptr;
	m_GreenMushRoom			= nullptr;
	m_BrickEvent			= GIFTBOX_BRICK_EVENT::EVENT_NONE; // When Brick doesnt move
	m_State					= BRICK_STATE::BRICK_NORMAL;
	m_CountCoin				= COIN_NUM_MAX;
	m_ResouceImage			= new CBonusResource(map);
	this->getBounding();
	this->loadSprite();
	return true;
}

void CBrick::updateEntity(CKeyBoard* device)
{

}

void CBrick::updateEntity(float deltaTime)
{
	switch (CCollision::CheckCollision(CPlayer::getInstance(), this))
	{
	case COLDIRECTION::COLDIRECTION_BOTTOM:
		if (m_State == BRICK_STATE::BRICK_NORMAL) {
			m_Velocity.y = VEL_DEFAULT_Y + BRICK_VELOCITY_MAX_Y;
			if (m_BrickType == BRICK_TYPE::BRICK_STAR ||
				m_BrickType == BRICK_TYPE::BRICK_GREENMUSHROOM) {
				m_State			= BRICK_STATE::BRICK_BOX;
				m_BrickEvent	= GIFTBOX_BRICK_EVENT::EVENT_PROCCESSING;
			}
			else if (m_BrickType == BRICK_TYPE::BRICK_COIN) {
				m_CountCoin--;
				if (m_CountCoin >= 7) {
					m_State		= BRICK_STATE::BRICK_NORMAL;
				}
				else {
					m_State		= BRICK_STATE::BRICK_BOX;
				}

				m_BrickEvent = GIFTBOX_BRICK_EVENT::EVENT_PROCCESSING;
			}
			else if (m_BrickType == BRICK_TYPE::BRICK_NONE && this->m_State == BRICK_STATE::BRICK_NORMAL){
				if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::BIG ||
					CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::FIRE ||
					CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::UNDYING)
				{
					m_BrickMini.push_back(new CBrickMini(this->map, this->m_Position, BRICKMINI_TYPE::BRICKMINI_LEFT_UP));
					m_BrickMini.push_back(new CBrickMini(this->map, vector3d(this->m_Position.x + 8, this->m_Position.y, 0), BRICKMINI_TYPE::BRICKMINI_LEFT_DOWN));
					m_BrickMini.push_back(new CBrickMini(this->map, vector3d(this->m_Position.x, this->m_Position.y + 8, 0), BRICKMINI_TYPE::BRICKMINI_RIGHT_UP));
					m_BrickMini.push_back(new CBrickMini(this->map, vector3d(this->m_Position.x + 8, this->m_Position.y + 8, 0), BRICKMINI_TYPE::BRICKMINI_RIGHT_DOWN));

					for (int i = 0; i < m_BrickMini.size(); i++)
					{
						CMapManager::getInstance()->pushBonusObject(m_BrickMini.at(i));
					}

					this->isDestroy = true;

					vector<CBaseEntity*>  tempList = CMapManager::getInstance()->getListBonus();
					tempList.erase(tempList.begin() + getIndex(tempList, this));

					CMapManager::getInstance()->setListBonus(tempList);

					tempList.clear();

					this->m_BrickEvent == GIFTBOX_BRICK_EVENT::EVENT_NONE;
				}

			}
		}
		else if (m_State == BRICK_STATE::BRICK_BOX) {
			m_Velocity.y = VEL_DEFAULT_Y;
		}
		break;
	case COLDIRECTION::COLDIRECTION_TOP:
		break;
	default:
		break;
	}

	if (m_Position.y >= (this->PrePos.y + this->m_listSprite.at(m_State)->getFrameInfo().Height / 2)){
		if (m_Velocity.y > 0){
			m_Velocity.y = CHANGE_DIRECTION(m_Velocity.y);
		}
	}

	if (SIGN(m_Velocity.y) == DIRECTION::DIRECTION_DOWN) {
		if (m_Position.y <= this->PrePos.y) {
			m_Velocity.y = VEL_DEFAULT_Y;
		}
	}

	m_Position = vector3d(m_Position.x, m_Position.y + (m_Velocity.y + SIGN(m_Velocity.y) * GRAVITATION)* deltaTime / 100, 0);

	if (m_Position.y <= this->PrePos.y) {
		m_Position.y = this->PrePos.y;

		if ((m_BrickType == BRICK_TYPE::BRICK_STAR && m_State == BRICK_STATE::BRICK_BOX) ||
			(m_BrickType == BRICK_TYPE::BRICK_COIN) ||
			(m_BrickType == BRICK_TYPE::BRICK_GREENMUSHROOM && m_State == BRICK_STATE::BRICK_BOX))
		{
			//m_Position.y = this->PrePos.y;
			if (m_BrickEvent == GIFTBOX_BRICK_EVENT::EVENT_PROCCESSING)
				m_BrickEvent = GIFTBOX_BRICK_EVENT::EVENT_DONE;
		}
	}

	if (m_BrickEvent == GIFTBOX_BRICK_EVENT::EVENT_DONE){
		if (m_BrickType == BRICK_TYPE::BRICK_STAR)
		{
			m_Star			= new CStar(vector3d(this->m_Position.x, this->PrePos.y + ADD_POS_Y, 0));
			m_Star->setVelocity(vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y + 2));
			CMapManager::getInstance()->pushInFirst(m_Star);
			m_BrickEvent	= GIFTBOX_BRICK_EVENT::EVENT_NONE;
			m_BrickType		= BRICK_TYPE::BRICK_NONE;
		}
		else if (m_BrickType == BRICK_TYPE::BRICK_COIN) {
			m_Coin			= new CCoinInBox(vector3d(this->m_Position.x, this->PrePos.y + ADD_POS_Y, 0));
			m_Coin->setVelocity(vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y + 5));
			CMapManager::getInstance()->pushInFirst(m_Coin);
			m_BrickEvent	= GIFTBOX_BRICK_EVENT::EVENT_NONE;
		}
		else if (this->m_BrickType == BRICK_TYPE::BRICK_GREENMUSHROOM)
		{
			m_GreenMushRoom = new CGreenMushroom(vector3d(this->m_Position.x, this->PrePos.y + ADD_POS_Y, 0));
			m_GreenMushRoom->setVelocity(vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y + 2));
			CMapManager::getInstance()->pushInFirst(m_GreenMushRoom);
			m_BrickEvent = GIFTBOX_BRICK_EVENT::EVENT_NONE;
			m_BrickType = BRICK_TYPE::BRICK_NONE;
		}
	}


}

void CBrick::drawEntity()
{
	this->m_listSprite.at(this->m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CBrick::updateEntity(RECT* camera)
{

}

void CBrick::setPosition(vector3d position) {
	m_Position = position;
}

void CBrick::setVelocity(vector2d velocity) {
	m_Velocity = velocity;
}

int	CBrick::getTagNodeId()
{
	return TAGNODE::BRICK;
}

int CBrick::getMap()
{
	return this->map;
}

int CBrick::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}