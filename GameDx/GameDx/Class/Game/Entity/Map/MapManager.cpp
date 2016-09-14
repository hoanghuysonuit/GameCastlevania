#include "MapManager.h"
#include <fstream>
#include "Class\Framework\Camera.h"
#include "Class\Game\Scene\PopupInfo.h"
#include "Class\Game\Entity\Enemy\CarnivorousPlants.h"
#include "Class\Game\Entity\Bonus\Brick.h"
#include "Class\Game\Entity\Bonus\GiftBox.h"
#include "Class\Game\Entity\Tile\Castle.h"
#include "Class\Game\Entity\Enemy\Mushroom.h"
#include "Class\Game\Entity\Enemy\Turtle.h"
#include "Class\Game\Entity\Enemy\CarnivorousPlants.h"
#include "Class\Game\Entity\Tile\Flag.h"
#include "Class\Game\Entity\Tile\FlagPole.h"
#include "Class\Game\Entity\Tile\FlagPoleHead.h"
#include "Class\Game\Entity\Tile\FlagPoleTail.h"
#include "Class\Game\Entity\Bonus\Coin.h"
#include "Class\Game\Entity\Tile\Elevator.h"



CMapManager* CMapManager::m_instance = NULL;

CMapManager::CMapManager()
{
	this->initMapInfo();
	this->loadEntityInMap();
}

CMapManager::~CMapManager()
{
	m_listAllMapInGame.clear();
	m_listBackground.clear();
	m_listBonus.clear();
	m_listEnemy.clear();
	m_listRectangeForCollision.clear();
	m_listBonusItem.clear();
}

CMapManager* CMapManager::getInstance()
{
	if (!m_instance)
		m_instance = new CMapManager();

	return m_instance;
}

vector<CBaseEntity*> CMapManager::getListEnemy()
{
	return m_listEnemy;
}

vector<CBaseEntity*>	CMapManager::getListBonus()
{
	return m_listBonus;
}

void CMapManager::setListBonus(vector<CBaseEntity*> list) {
	m_listBonus = list;

}

vector<CTiless*> CMapManager::getListBackground()
{
	return m_listBackground;
}

vector<CBox2D*>	CMapManager::getListRect()
{
	return m_listRectangeForCollision;
}

vector<CBaseEntity*> CMapManager::getListBonusItem()
{
	return m_listBonusItem;
}

void CMapManager::setListBonusItem(vector<CBaseEntity*> list)
{
	this->m_listBonusItem = list;
}

void CMapManager::setListEnemy(vector<CBaseEntity*> list)
{
	this->m_listEnemy = list;
}

vector<MapInfo*> CMapManager::getListMapInGame()
{
	return m_listAllMapInGame;
}



bool CMapManager::initMapInfo()
{
	m_listAllMapInGame.push_back(new MapInfo("1-1", "Resource//Data//1-1.txt", 3584, 240));
	m_listAllMapInGame.push_back(new MapInfo("1-2", "Resource//Data//1-2.txt", 3584, 240));
	m_listAllMapInGame.push_back(new MapInfo("1-3", "Resource//Data//1-3.txt", 3584, 240));
	return true;
}

int CMapManager::getCurrentMapINT()
{
	string temp = CPopUpInfo::getInstance()->getMapName();

	if (temp == "1-1")
		return 1;
	if (temp == "1-2")
		return 2;
	if (temp == "1-3")
		return 3;
	return -1;
}

bool CMapManager::loadEntityInMap()
{

	ifstream data;

	string filePath = "Resource\\Data\\" + CPopUpInfo::getInstance()->getMapName() + ".txt";

	// convert to unicode
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, wstr, wchars_num);

	data.open(wstr);

	vector2d positionEntity;
	vector2d size;
	int type;

	while (data >> type >> positionEntity.x >> positionEntity.y >> size.x >> size.y)
	{
		if (type == TODI::TODI_STARS)
			m_listBonus.push_back(new CBrick(this->getCurrentMapINT(), positionEntity, BRICK_TYPE::BRICK_STAR));
		if (type == TODI::TODI_COININBOX)
			m_listBonus.push_back(new CBrick(this->getCurrentMapINT(), positionEntity, BRICK_TYPE::BRICK_COIN));
		if (type == TODI::TODI_BRICK)
			m_listBonus.push_back(new CBrick(this->getCurrentMapINT(), positionEntity, BRICK_TYPE::BRICK_NONE));
		if (type == TODI::TODI_GREEN_MUSHROOM_BOX)
			m_listBonus.push_back(new CBrick(this->getCurrentMapINT(), positionEntity, BRICK_TYPE::BRICK_GREENMUSHROOM));
		if (type == TODI::TODI_COIN)
			m_listBonus.push_back(new CCoin(positionEntity));

		if (type == TODI::TODI_RED_MUSHROOM_BOX)
			m_listBonus.push_back(new CGiftBox(positionEntity, GIFTBOX_TYPE::GIFTBOX_ITEMINBOX_TYPE));
		if (type == TODI::TODI_GIFT_BOX)
			m_listBonus.push_back(new CGiftBox(positionEntity, GIFTBOX_TYPE::GIFTBOX_COIN));

		if (type == TODI::TODI_FLAG_POLE)
			m_listBonus.push_back(new CFlagPole(positionEntity));
		if (type == TODI::TODI_FLAG_POLE_HEAD)
			m_listBonus.push_back(new CFlagPoleHead(positionEntity));
		if (type == TODI::TODI_GREEN_FLAG)
			m_listBonus.push_back(new CFlag(positionEntity));
		if (type == TODI::TODI_FLAG_POLE_TAIL)
			m_listBonus.push_back(new CFlagPoleTail(positionEntity));

		if (type == TODI::TODI_ELEVATOR_UP)
			m_listBonus.push_back(new Elevator(positionEntity, ELEVATOR_STATE::UP_DOWN));
		if (type == TODI::TODI_ELEVATOR_DOWN)
			m_listBonus.push_back(new Elevator(positionEntity, ELEVATOR_STATE::UP));

		if (type == TODI::TODI_MUSHROOM)
			m_listEnemy.push_back(new CMushroom(positionEntity,							EnemyStyle::TOF_RED_MUSHROOM));
		if (type == TODI::TODI_BLUE_CARNIVOROUSPLANTS)
			m_listEnemy.push_back(new CCarnivorousPlants(positionEntity, CARNIVOROUS_PLANT_TYPE::BLUE_CARNIVOROUS_PLANT));
		if (type == TODI::TODI_GREEN_CARNIVOROUSPLANTS)
			m_listEnemy.push_back(new CCarnivorousPlants(positionEntity, CARNIVOROUS_PLANT_TYPE::GREEN_CARNIVOROUS_PLANT));

		/*if (type == TODI::TODI_CASTLE)
			m_listBackground.push_back(new CTiless(positionEntity,						TileStyle::TOF_CASTTLE));
			*/
		if ((type == TODI::TODI_CEMENT))
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CEMENT_BARRIER_RED));
		if ((type == TODI::TODI_BLUE_STAIR))
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CEMENT_BARRIER_BLUE));

		if ((type == TODI::TODI_LANDSCAPE))
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CEMENT_LANE_RED));
		if (type == TODI::TODI_GREEN_LANDSCAPE)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CEMENT_LANE_BLE));

		if (type == TODI::TODI_CLOUND_ONE)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CLOUND_ONE_MEMBER));
		if (type == TODI::TODI_CLOUND_DOUBLE)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CLOUND_TOW_MEMBER));
		if (type == TODI::TODI_CLOUND_TRIPPLE)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_CLOUND_THREE_MEMBER));

		if (type == TODI::TODI_GRASS_ONE_BRUSH)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_GRASS_ONE_BUSH));
		if (type == TODI::TODI_GRASS_DOUBLE_BRUSH)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_GRASS_TOW_BUSH));
		if (type == TODI::TODI_GRASS_TRIPPLE_BRUSH)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_GRASS_THREE_BUSH));

		if (type == TODI::TODI_HEAD_MOUNTAIN)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_MOUNTAIN_SMALL));
		if (type == TODI::TODI_TAIL_MOUNTAIN)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_MOUNTAIN_BIG));

		if (type == TODI::TODI_PIPE_HEAD)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_PIPE_HEAD_DOWN));
		if (type == TODI::TODI_PIPE_HEAD_BODY)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_PIPE_HEAD_BODY_DOWN));
		if (type == TODI::TODI_PIPE_BODY)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_PIPE_BODY_DOWN));

		if (type == TODI::TODI_BRICK_TILE)
			m_listBackground.push_back(new CTiless(positionEntity, TileStyle::TOF_BRICK_TILE));

		if (type == TODI::TODI_RECTANGLE) {
				m_listRectangeForCollision.push_back(new CBox2D(positionEntity.x, positionEntity.y - 16, size.x, size.y));
		}
	}

	return true;
}

void CMapManager::pushBonusObject(CBaseEntity* entity)
{
	m_listBonusItem.push_back(entity);
}

void CMapManager::popBonusObject()
{
	m_listBonusItem.pop_back();
}

void CMapManager::pushInFirst(CBaseEntity* entity)
{
	m_listBonusItem.insert(m_listBonusItem.begin(), entity);
}

void CMapManager::removeInFirst() {
	if (!m_listBonusItem.empty())
		m_listBonusItem.erase(m_listBonusItem.begin());
}

void CMapManager::removeEntity(vector<CBaseEntity*>& list, int tagnode)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (list.at(i)->getTagNodeId() == tagnode)
			list.erase(list.begin() + i);
	}

}

void CMapManager::resetVectorData(){

	CTiless* temp;
	while (!m_listBackground.empty())
	{
		temp = m_listBackground.back();
		m_listBackground.pop_back();
		delete temp;
		temp = NULL;
	}
	m_listBackground.clear();

	CBaseEntity* tempEnemy;
	while (!m_listEnemy.empty())
	{
		tempEnemy = m_listEnemy.back();
		m_listEnemy.pop_back();
		delete tempEnemy;
		tempEnemy = NULL;
	}
	m_listEnemy.clear();

	CBaseEntity* tempBonus;
	while (!m_listBonus.empty())
	{
		tempBonus = m_listBonus.back();
		m_listBonus.pop_back();
		delete tempBonus;
		tempBonus = NULL;
	}
	m_listBonus.clear();

	CBox2D* tempRect;
	while (!m_listRectangeForCollision.empty())
	{
		tempRect = m_listRectangeForCollision.back();
		m_listRectangeForCollision.pop_back();
		delete tempRect;
		tempRect = NULL;
	}
	m_listRectangeForCollision.clear();

	CBaseEntity* temoBonusItem;
	while (!m_listBonusItem.empty())
	{
		temoBonusItem = m_listBonusItem.back();
		m_listBonusItem.pop_back();
		delete temoBonusItem;
		temoBonusItem = NULL;
	}
	m_listBonusItem.clear();
}

void CMapManager::resetToMap(int map)
{
	this->resetVectorData();
	CPopUpInfo::getInstance()->setMapName(CMapManager::getInstance()->getListMapInGame().at(map)->m_mapName);
	this->loadEntityInMap();

}