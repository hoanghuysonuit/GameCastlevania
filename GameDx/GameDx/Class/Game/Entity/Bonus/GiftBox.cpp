#include "GiftBox.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\SweptAABB.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"

CGiftBox::CGiftBox()
{
	this->initEntity();
}

CGiftBox::CGiftBox(vector2d pos, GIFTBOX_TYPE type)
{
	this->GIFTBOX_PRE_POSITION_Y = pos.y;

	this->m_Position.x = pos.x;
	this->m_Position.y = pos.y;

	this->m_Bounding = new CBox2D(0, 0, 0, 0);

	this->m_Velocity = vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y);

	this->m_GiftBoxType = type;

	this->initEntity();

	this->GIFTBOX_PRE_POSITION_Y_MAX = pos.y + this->m_listSprite.at(0)->getFrameInfo().Height;
}

CGiftBox:: ~CGiftBox()
{
	SAFE_RELEASE(m_Coin);
	SAFE_RELEASE(m_itemInBox);

	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CGiftBox::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::GIFT_BOX, GIFTBOX_STATE::GIFTBOX), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::GIFT_BOX, GIFTBOX_STATE::GIFTBOX_NORMAL), 1, 1, 1, 0));
	return true;
}

bool CGiftBox::initEntity()
{
	m_itemInBox = nullptr;
	m_Coin = nullptr;

	this->m_GiftBoxEvent = GIFTBOX_BRICK_EVENT::EVENT_NONE;
	this->m_State = GIFTBOX_STATE::GIFTBOX_NORMAL;

	this->m_ResouceImage = new CBonusResource();
	this->loadSprite();
	this->getBounding();

	this->getBounding();

	return true;
}

void CGiftBox::updateEntity(CKeyBoard* device)
{
}

void CGiftBox::updateEntity(float deltaTime)
{
	switch (CCollision::CheckCollision(CPlayer::getInstance(), this))
	{
	case COLDIRECTION::COLDIRECTION_BOTTOM:
		if (this->m_State == GIFTBOX_STATE::GIFTBOX_NORMAL)
		{
			m_Velocity.y = VEL_DEFAULT_Y + GIFTBOX_VELOCITY_MAX_Y;

			this->m_GiftBoxEvent = GIFTBOX_BRICK_EVENT::EVENT_PROCCESSING;
			this->m_State = GIFTBOX_STATE::GIFTBOX;
		}
		break;
	case COLDIRECTION::COLDIRECTION_TOP:
		break;
	default:
		break;
	}

	if (m_Position.y >= GIFTBOX_PRE_POSITION_Y_MAX)
	{
		if (m_Velocity.y > 0)
		{
			m_Velocity.y = CHANGE_DIRECTION(m_Velocity.y);
		}
	}

	if (SIGN(m_Velocity.y) == DIRECTION::DIRECTION_DOWN)
	{
		if (m_Position.y <= GIFTBOX_PRE_POSITION_Y)
		{
			m_Velocity.y = VEL_DEFAULT_Y;
		}
	}

	m_Position = vector3d(m_Position.x, m_Position.y + (m_Velocity.y + SIGN(m_Velocity.y) * GRAVITATION)* deltaTime / 100, 0);

	if (this->m_Position.y <= GIFTBOX_PRE_POSITION_Y &&
		this->m_State == GIFTBOX_STATE::GIFTBOX)
	{
		this->m_Position.y = GIFTBOX_PRE_POSITION_Y;

		if (this->m_GiftBoxType == GIFTBOX_TYPE::GIFTBOX_ITEMINBOX_TYPE ||
			this->m_GiftBoxType == GIFTBOX_TYPE::GIFTBOX_COIN)
		{
			if (this->m_GiftBoxEvent == GIFTBOX_BRICK_EVENT::EVENT_PROCCESSING)
				this->m_GiftBoxEvent = GIFTBOX_BRICK_EVENT::EVENT_DONE;
		}
	}

	if (this->m_GiftBoxEvent == GIFTBOX_BRICK_EVENT::EVENT_DONE)
	{
		if (this->m_GiftBoxType == GIFTBOX_TYPE::GIFTBOX_ITEMINBOX_TYPE)
		{
			this->m_itemInBox = new CIteminbox(vector2d(this->m_Position.x, GIFTBOX_PRE_POSITION_Y + ADD_POS_Y));
			this->m_itemInBox->setVelocity(vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y + 3));
			CMapManager::getInstance()->pushInFirst(m_itemInBox);
		}
		else if (this->m_GiftBoxType == GIFTBOX_TYPE::GIFTBOX_COIN)
		{
			m_Coin = new CCoinInBox(vector3d(this->m_Position.x, GIFTBOX_PRE_POSITION_Y + ADD_POS_Y, 0));
			m_Coin->setVelocity(vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y + 5));
			CMapManager::getInstance()->pushInFirst(m_Coin);
		}

		this->m_GiftBoxEvent = GIFTBOX_BRICK_EVENT::EVENT_NONE;
		this->m_GiftBoxType = GIFTBOX_TYPE::GIFTBOX_NONE;

	}
}

void CGiftBox::drawEntity()
{
	this->m_listSprite.at(this->m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CGiftBox::updateEntity(RECT* camera)
{
}

void CGiftBox::setPosition(vector3d vector)
{
	this->m_Position = vector;
}

int	CGiftBox::getTagNodeId()
{
	return TAGNODE::GIFT_BOX;
}

int CGiftBox::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}