#include "Mushroom.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Utill\ResourceManager\EnermyResource.h"

CMushroom::CMushroom()
{
	this->m_Bounding	= new CBox2D(0, 0, 0, 0);
	this->m_Velocity	= vector2d(0.1, -0.98);
	this->m_Direction	= vector2d(DIRECTION::DIRECTION_LEFT, DIRECTION::DIRECTION_DOWN);
	this->initEntity();
}

CMushroom::CMushroom(vector2d vect, int type){
	m_Position.x		= vect.x;
	m_Position.y		= vect.y;
	m_Type				= type;

	this->m_Bounding	= new CBox2D(0, 0, 0, 0);
	this->m_Velocity	= vector2d(5, 9.8);
	this->m_Direction	= vector2d(DIRECTION::DIRECTION_LEFT, DIRECTION::DIRECTION_DOWN);

	this->initEntity();
}

CMushroom::~CMushroom()
{
	SAFE_RELEASE(this->m_ResouceImage);
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool	CMushroom::loadSprite(){
	switch (m_Type)
	{
	case EnemyStyle::TOF_RED_MUSHROOM:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::MUSHROOM, MUSHROOM_STATE::MUSH_RUN), 1, 2));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::MUSHROOM, MUSHROOM_STATE::MUSH_IS_ACTTACKED), 1, 1));
		break;
	case EnemyStyle::TOF_BLUE_MUSHROOM:
		break;
	default:
		return false;
	}
	return true;
}

bool	CMushroom::initEntity()
{
	this->m_ResouceImage		= new CEnermyResource();
	this->loadSprite();
	this->m_State				= MUSHROOM_STATE::MUSH_RUN;
	this->getBounding();
	return true;
}

void	CMushroom::updateEntity(float deltaTime)
{
	if (m_State == MUSHROOM_STATE::MUSH_RUN)
	{
		m_Position.x += m_Velocity.x*deltaTime / 1000;
		m_Position.y -= m_Velocity.y*deltaTime / 100;
	}

	if (m_State == MUSHROOM_STATE::MUSH_IS_ACTTACKED)
	{
		this->isDestroy = true;
	}

	updateCollision(deltaTime);
}

void	CMushroom::updateEntity(CKeyBoard* device)
{
	/*if (device->KeyPress(DIK_DELETE))

	if (m_State == MUSHROOM_STATE::MUSH_RUN)
		m_State = MUSHROOM_STATE::MUSH_IS_ACTTACKED;
	else
		m_State = MUSHROOM_STATE::MUSH_RUN;*/
}

void	CMushroom::updateEntity(RECT* rectCamera)
{

}

void	CMushroom::updateCollision(float deltaTime)
{
	this->getBounding().setVelocity(this->getVelocity());

	vector<CBox2D*> listRect = CMapManager::getInstance()->getListRect();

	for (int i = 0; i < listRect.size(); ++i) {
		if (this->m_State != MUSHROOM_STATE::MUSH_IS_ACTTACKED) {
			this->getBounding().setVelocity(this->getVelocity());
			switch (CCollision::CheckCollision(this->getBounding(), *(listRect.at(i))))
			{
			case COLDIRECTION::COLDIRECTION_TOP:
				this->m_Position.y = listRect.at(i)->getY() + this->getBounding().getHeight() / 2;
				break;
			case COLDIRECTION::COLDIRECTION_LEFT:
				if (m_Velocity.x >= 0) {
					m_Velocity.x = -5.8;
				}
				break;
			case COLDIRECTION::COLDIRECTION_RIGHT:
				m_Velocity.x = 5.8;
				break;
			default:
				break;
			}
		}
	}

	/* Collision with Player*/
	if (this->m_State != MUSHROOM_STATE::MUSH_IS_ACTTACKED) {
		this->getBounding().setVelocity(this->getVelocity());
		//CPlayer::getInstance()->getBounding().setVelocity(CPlayer::getInstance()->getVelocity());
		switch (CCollision::CheckCollision(this, CPlayer::getInstance()))
		{
		case COLDIRECTION::COLDIRECTION_BOTTOM:
			m_State = MUSHROOM_STATE::MUSH_IS_ACTTACKED;
			this->isDestroy = true;
			break;
		default:
			break;
		}
	}

	if (m_Position.x <= 0)
		m_Velocity.x *= -1;
}

void	CMushroom::drawEntity()
{
	m_listSprite.at(m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 5);
}

int CMushroom::getTagNodeId(){
	return TAGNODE::MUSHROOM;
}

int CMushroom::getObjectType() {
	return OBJECT_TYPE::TYPE_ENERMY;
}

class CMapManager;
