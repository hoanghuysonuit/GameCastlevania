#include "Tile.h"

CTile::CTile()
{
	this->initEntity();
}

CTile::CTile(vector3d pos, int State)
{
	m_Pos = pos;
	m_Index = State;
}


CTile::~CTile()
{
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

bool CTile::initEntity()
{
	m_Position = vector3d(50, 100, 0.5);
	this->loadSprite();
	this->m_Bounding = new CBox2D(0, 0, 0, 0);

	return true;
}

void CTile::updateEntity(float deltaTime)
{

}

void CTile::updateEntity(CKeyBoard* device)
{

}

void CTile::updateEntity(RECT* rectCamera)
{

}

void CTile::drawEntity()
{
	for (int i = 0; i < m_listSprite.size(); i++){
		//this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(vector3d(this->m_Bounding->getX(), m_Bounding->getY(), 0)), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);

		this->m_listSprite.at(i)->Render(CCamera::setPositionEntity(vector3d(m_Position)), vector2d(SIGN(m_Position.x), SIGN(m_Position.y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	}
}

bool CTile::loadSprite()
{
	m_listSprite.push_back(new CSprite(L"Resource//Image//Game//Sprites//Others//bar_mana_gutman.png"));
	return true;
}

int CTile::getTagNodeId() {
	return TAGNODE::TILE;
}

int CTile::getObjectType() {
	return OBJECT_TYPE::TYPE_TILE;
}