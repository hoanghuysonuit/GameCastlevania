#include "Tiless.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"

CTiless::CTiless()
{
	m_Position			= vector3dZero;
	m_ID				= -1;
	m_Bounding			= new CBox2D(m_Position.x, m_Position.y, 0, 0);

	this->initEntity();
}

CTiless::CTiless(vector2d pos, int type)
{
	m_Position.x		= pos.x;
	m_Position.y		= pos.y;
	m_ID				= type;

	this->initEntity();

}
CTiless::~CTiless()
{
	/*if (!m_listSprite.empty())
		m_listSprite.clear();*/
	SAFE_RELEASE(this->m_ResouceImage);

	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}


bool	CTiless::loadSprite()
{
	switch (m_ID)
	{
	case TileStyle::TOF_GRASS_LEFT:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_LEFT)));
		break;
	case TileStyle::TOF_GRASS_RIGHT:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_RIGHT)));
		break;
	case TileStyle::TOF_GRASS_MIDDLE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_MIDDLE)));
		break;
	case TileStyle::TOF_GRASS_ONE_BUSH:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_ONE_BUSH)));
		break;
	case TileStyle::TOF_GRASS_TOW_BUSH:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_TOW_BUSH)));
		break;
	case TileStyle::TOF_GRASS_THREE_BUSH:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_GRASS_THREE_BUSH)));
		break;

	case TileStyle::TOF_CASTTLE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CASTTLE)));
		break;

	case TileStyle::TOF_PIPE_HEAD_DOWN:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_PIPE_HEAD_DOWN)));
		break;
	case TileStyle::TOF_PIPE_HEAD_BODY_DOWN:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_PIPE_HEAD_BODY_DOWN)));
		break;
	case TileStyle::TOF_PIPE_BODY_DOWN:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_PIPE_BODY_DOWN)));
		break;
	case TileStyle::TOF_PIPE_HEAD_RIGHT:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_PIPE_HEAD_RIGHT)));
		break;
	case TileStyle::TOF_PIPE_BODY_RIGHT:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_PIPE_BODY_RIGHT)));
		break;

	case TileStyle::TOF_CEMENT_PIPE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CEMENT_PIPE)));
		break;
	case TileStyle::TOF_CEMENT_BARRIER_RED:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CEMENT_BARRIER_RED)));
		break;
	case TileStyle::TOF_CEMENT_BARRIER_BLUE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CEMENT_BARRIER_BLUE)));
		break;
	case TileStyle::TOF_CEMENT_LANE_RED:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CEMENT_LANE_RED)));
		break;
	case TileStyle::TOF_CEMENT_LANE_BLE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CEMENT_LANE_BLE)));
		break;
	case TileStyle::TOF_CLOUND_ONE_MEMBER:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CLOUND_ONE_MEMBER)));
		break;
	case TileStyle::TOF_CLOUND_TOW_MEMBER:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CLOUND_TOW_MEMBER)));
		break;
	case TileStyle::TOF_CLOUND_THREE_MEMBER:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_CLOUND_THREE_MEMBER)));
		break;

	case TileStyle::TOF_MOUNTAIN_SMALL:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_MOUNTAIN_SMALL)));
		break;

	case TileStyle::TOF_MOUNTAIN_BIG:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_MOUNTAIN_BIG)));
		break;
	case TileStyle::TOF_BRICK_TILE:
		m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_BRICK_TILE)));
		break;
	default:
		return false;
	}

	return true;
}

bool	CTiless::initEntity()
{
	this->m_ResouceImage = new CTileResource();
	this->loadSprite();

	m_State = 0;
	m_Bounding = new CBox2D();

	this->getBounding();
	return true;
}

void	CTiless::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); ++i)
	/*if (m_ID == TileStyle::TOF_BRICK_TILE)
		m_listSprite.at(i)->Render(CCamera::getInstance()->setPositionEntity(m_Position), vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE);
	else*/ if (m_ID == TileStyle::TOF_MOUNTAIN_BIG || m_ID == TOF_MOUNTAIN_SMALL || TOF_PIPE_HEAD_DOWN)
		m_listSprite.at(i)->Render(CCamera::getInstance()->setPositionEntity(vector3d(m_Position.x, m_Position.y - 16, 0.5f)), vector2d(1, 1), 0, DRAWCENTER_LEFT_BOTTOM, true, 10);
	else
		m_listSprite.at(i)->Render(CCamera::getInstance()->setPositionEntity(m_Position), vector2d(1, 1), 0, DRAWCENTER_LEFT_TOP, true, 10);
}

CBox2D  CTiless::getBounding()
{
	if (m_listSprite.size())
	{
		m_Bounding->setX(m_Position.x);
		m_Bounding->setY(m_Position.y);
		m_Bounding->setWidth(m_listSprite.at(0)->getFrameInfo().Width);
		m_Bounding->setHeight(m_listSprite.at(0)->getFrameInfo().Height);
	}
	return *m_Bounding;
}

const char*	CTiless::getTagNode() {
	return nullptr;
}

int CTiless::getObjectType() {
	return OBJECT_TYPE::TYPE_TILE;
}

int	CTiless::getTagNodeId() {
	return TAGNODE::TILE;
}

vector3d CTiless::getPosition() {
	return m_Position;
}