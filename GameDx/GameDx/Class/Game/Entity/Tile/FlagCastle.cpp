#include "FlagCastle.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"


CFlagCastle::CFlagCastle()
{
	this->initEntity();
}


CFlagCastle:: ~CFlagCastle()
{
	SAFE_RELEASE(this->m_ResouceImage);
}

bool CFlagCastle::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CASTLE_FLAG), 1, 1, 1, 0));
	return true;
}

bool CFlagCastle::initEntity()
{
	m_Position = vector3d(180, 140, 0);
	this->m_ResouceImage = new CTileResource();
	this->loadSprite();
	this->m_Bounding = new CBox2D(0, 0, 0, 0);
	this->m_Velocity = vector2d(0, 0);
	m_TagNode = "FlagCastle";
	return true;
}

void CFlagCastle::updateEntity(CKeyBoard* device)
{

}
void CFlagCastle::updateEntity(float deltaTime)
{
	if (CPlayer::getInstance()->getPosition().x >= 180) {
		static int count = 0;
		if (count > 100) {
			if (m_Position.y <= 160) {
				m_Velocity.y = 2.5;
				m_Position.y = m_Position.y + m_Velocity.y * deltaTime / 100;
			}
			else
				m_Velocity.y = 0;
		}
		else
			count++;
	}

}

void CFlagCastle::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++)
		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CFlagCastle::updateEntity(RECT* camera)
{

}


void CFlagCastle::setPosition(vector3d position) {
	m_Position = position;
}

void CFlagCastle::setVelocity(vector2d velocity) {
	m_Velocity = velocity;
}
