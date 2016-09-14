#include "Turtle.h"

#include "Class\Game\Utill\ResourceManager\EnermyResource.h"


CTurtule::CTurtule()
{
	this->initEntity();
}

CTurtule::~CTurtule()
{
	SAFE_RELEASE(m_ResouceImage);

	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

CTurtule::CTurtule(vector2d, int type)
{
	this->initEntity();

}

bool CTurtule::initEntity()
{
	m_Position = vector3d(50, 100, 0.5);

	m_State = TURTLE_STATE::TURTLE_RUN;
	m_TagNode = "Turtle";
	m_Velocity = vector2d(4, 2.5);

	this->m_ResouceImage = new CEnermyResource(TAGNODE::TURTLE);

	this->loadSprite();
	this->m_Bounding = new CBox2D(0, 0, 0, 0);

	return true;
}

bool CTurtule::loadSprite()
{
	if (m_listSprite.size() > 0) {
		m_listSprite.clear();
	}

	switch (m_Type)
	{
	case TURTLE_TAG::GREEN:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::GREEN, TURTLE_STATE::TURTLE_RUN), 1, 2, 2, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::GREEN, TURTLE_STATE::TURTLE_ENSCONSE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::GREEN, TURTLE_STATE::TURTLE_INDENT), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::GREEN, TURTLE_STATE::TURTLE_FLY), 1, 2, 2, 0));

		break;
	case TURTLE_TAG::RED:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::RED, TURTLE_STATE::TURTLE_RUN), 1, 2, 2, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::RED, TURTLE_STATE::TURTLE_ENSCONSE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::RED, TURTLE_STATE::TURTLE_INDENT), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::RED, TURTLE_STATE::TURTLE_FLY), 1, 2, 2, 0));
		break;
	case TURTLE_TAG::NAVI:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::NAVI, TURTLE_STATE::TURTLE_RUN), 1, 2, 2, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::NAVI, TURTLE_STATE::TURTLE_ENSCONSE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::NAVI, TURTLE_STATE::TURTLE_INDENT), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TURTLE_TAG::NAVI, TURTLE_STATE::TURTLE_FLY), 1, 2, 2, 0));
		break;
	default:
		break;
	}

	return true;
}

void CTurtule::updateEntity(float deltaTime)
{
}

void CTurtule::updateEntity(RECT* camera) {

}

void CTurtule::updateEntity(CKeyBoard* input)
{

}

void CTurtule::drawEntity()
{
	if (m_State == TURTLE_STATE::TURTLE_DIE)
	{
		m_listSprite.at(m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Velocity.x) * (-1), abs(m_Velocity.y / m_Velocity.y) * -1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	}
	else
	{
		m_listSprite.at(m_State)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Velocity.x) * (-1), abs(m_Velocity.y / m_Velocity.y) * 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	}
}

int	CTurtule::getTagNodeId() {
	return TAGNODE::TURTLE;
}

int CTurtule::getObjectType() {
	return OBJECT_TYPE::TYPE_ENERMY;
}