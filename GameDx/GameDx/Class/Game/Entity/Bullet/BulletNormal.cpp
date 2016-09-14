#include "BulletNormal.h"
#include <math.h>
#include "Class\Game\Entity\Player\Player.h"

CBulletNormal::CBulletNormal()
{
	this->initEntity();
}


CBulletNormal::~CBulletNormal()
{
}

bool	CBulletNormal::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(CInfomationResource::fireMarioBullet, 1, 1, 1, 0));
	//this->m_listSprite.push_back(new CSprite(CInfomationResource::fireMarioBullet1, 1, 1, 1, 0));
	//this->m_listSprite.push_back(new CSprite(CInfomationResource::fireMarioBullet2, 1, 1, 1, 0));
	return	true;
}

bool	CBulletNormal::initEntity()
{
	m_Position = vector3d(20, 50, 0);
	this->m_Bounding = new CBox2D(0, 0, 0, 0);
	m_State = BULLETSTATE::BULLET_STATE_SHOW;
	m_Velocity = vector2d(9.8, 9.8);

	temp = 1;

	this->loadSprite();

	return true;
}

void	CBulletNormal::updateEntity(float deltaTime)
{
	switch (m_State)
	{
	case BULLETSTATE::BULLET_STATE_SHOW:
		m_Position.x += 1*sin((2 * PI / 6)) * CPlayer::getInstance()->m_Direction.at(DIRECTIONINDEX::DIRECTION_X);
		m_Position.y += 3*cos(4*PI*deltaTime/4 + PI / 6);
		if (m_Position.y > 100 || m_Position.y < 50)
			temp *= -1;
		break;
	case BULLETSTATE::BULLET_STATE_DIE:
		break;
	default:
		break;
	}
}

void	CBulletNormal::updateEntity(CKeyBoard* device)
{

}

void	CBulletNormal::updateEntity(RECT* camera) {

}

void	CBulletNormal::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); ++i)
	m_listSprite.at(i)->Render(CCamera::setPositionEntity(vector3d(m_Position)), vector2d(SIGN(m_Velocity.x), SIGN(m_Velocity.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

vector3d CBulletNormal::getPosition()
{

	return m_Position;
}

void	CBulletNormal::setState(int newState)
{
	m_State = newState;
}

int		CBulletNormal::getState()
{
	return m_State;
}