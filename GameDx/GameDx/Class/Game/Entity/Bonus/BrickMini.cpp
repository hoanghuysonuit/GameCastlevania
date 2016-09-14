#include "BrickMini.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\Bonus\CoinInBox.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Utill\ResourceManager\BonusResource.h"

CBrickMini::CBrickMini()
{
	this->initEntity();
}

CBrickMini::CBrickMini(int map, vector3d position, BRICKMINI_TYPE type)
{
	this->map				= CMapManager::getInstance()->getCurrentMapINT();;
	this->m_ResouceImage	= new CBonusResource(this->map);

	m_Position.x			= position.x;
	m_Position.y			= position.y;
	m_State					= type;

	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	this->m_Velocity		= vector2d(VEL_DEFAULT_X, VEL_DEFAULT_Y);

	this->getBounding();
	this->initEntity();
}

CBrickMini:: ~CBrickMini()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

bool CBrickMini::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICKMINI, BRICKMINI_TYPE::BRICKMINI_LEFT_UP), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICKMINI, BRICKMINI_TYPE::BRICKMINI_LEFT_DOWN), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICKMINI, BRICKMINI_TYPE::BRICKMINI_RIGHT_UP), 1, 1, 1, 0));
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TAGNODE::BRICKMINI, BRICKMINI_TYPE::BRICKMINI_RIGHT_DOWN), 1, 1, 1, 0));

	return true;
}

bool CBrickMini::initEntity()
{
	this->loadSprite();
	return true;
}

void CBrickMini::updateEntity(CKeyBoard* device)
{

}

void CBrickMini::updateEntity(float deltaTime)
{
	if (this->m_State == BRICKMINI_TYPE::BRICKMINI_LEFT_UP)
	{
		this->m_Position.x += BRICKMINI_UP_VELOCITY * cos(PI / 3);
		this->m_Position.y += (BRICKMINI_UP_VELOCITY * sin(PI / 3) + GRAVITATION) * deltaTime / 70;
	}
	else if (this->m_State == BRICKMINI_TYPE::BRICKMINI_LEFT_DOWN)
	{
		this->m_Position.x += BRICKMINI_DOWN_VELOCITY * cos(7 * PI / 18);
		this->m_Position.y += (BRICKMINI_DOWN_VELOCITY * sin(7 * PI / 18) + GRAVITATION) * deltaTime / 70;
	}
	else if (this->m_State == BRICKMINI_TYPE::BRICKMINI_RIGHT_UP)
	{
		this->m_Position.x += BRICKMINI_UP_VELOCITY * cos(2 * PI / 3);
		this->m_Position.y += (BRICKMINI_UP_VELOCITY * sin(2 * PI / 3) + GRAVITATION)* deltaTime / 70;
	}
	else if (this->m_State == BRICKMINI_TYPE::BRICKMINI_RIGHT_DOWN)
	{
		this->m_Position.x += BRICKMINI_DOWN_VELOCITY * cos(11 * PI / 18);
		this->m_Position.y += (BRICKMINI_DOWN_VELOCITY * sin(11 * PI / 18) + GRAVITATION)* deltaTime / 70;
	}
	if (this->m_Position.y <= 20)
	{
		vector<CBaseEntity*> tempBonusList = CMapManager::getInstance()->getListBonusItem();
		CMapManager::getInstance()->removeEntity(tempBonusList, TAGNODE::BRICKMINI);
		CMapManager::getInstance()->setListBonusItem(tempBonusList);
		tempBonusList.clear();
	}
}

void CBrickMini::drawEntity()
{
	this->m_listSprite.at(this->m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CBrickMini::updateEntity(RECT* camera)
{

}

void CBrickMini::setPosition(vector3d position) {
	m_Position = position;
}

void CBrickMini::setVelocity(vector2d velocity) {
	m_Velocity = velocity;
}

int	CBrickMini::getTagNodeId()
{
	return TAGNODE::BRICKMINI;
}

int CBrickMini::getObjectType() {
	return OBJECT_TYPE::TYPE_BONUS;
}