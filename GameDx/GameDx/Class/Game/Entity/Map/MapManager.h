#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "Class\Game\Entity\Map\Tile.h"
#include "Class\Game\Entity\StaticEntity.h"
#include "Class\Game\Entity\Map\Tiless.h"

using namespace std;

class CMapManager
{
public:
	CMapManager();
	~CMapManager();

	bool	initMapInfo();
	bool	loadEntityInMap();

public:
	vector<CBaseEntity*>	getListEnemy();
	vector<CBaseEntity*>	getListBonus();
	void					setListBonus(vector<CBaseEntity*> list);
	vector<CTiless*>		getListBackground();
	vector<CBox2D*>			getListRect();
	vector<CBaseEntity*>    getListBonusItem();
	void					setListBonusItem(vector<CBaseEntity*> list);
	void					setListEnemy(vector<CBaseEntity*> list);
	static CMapManager*		getInstance();

	vector<MapInfo*>		getListMapInGame();
	int						getCurrentMapINT();

	void					pushBonusObject(CBaseEntity* entity);
	void					popBonusObject();
	void					pushInFirst(CBaseEntity* entity);
	void					removeInFirst();
	void					removeEntity(vector<CBaseEntity*>& list, int tagnode);

	void					CMapManager::resetVectorData();
	void					CMapManager::resetToMap(int map);

private:
	static CMapManager*		m_instance;

	vector<MapInfo*>		m_listAllMapInGame;

	vector<CTiless*>		m_listBackground;
	vector<CBaseEntity*>	m_listEnemy;
	vector<CBaseEntity*>	m_listBonus;
	vector<CBox2D*>			m_listRectangeForCollision;

	// create list for object created while playing Game
	vector<CBaseEntity*>    m_listBonusItem;
};


#endif