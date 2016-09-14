#include "QuadTree.h"
#include "Class\Game\Entity\Map\MapManager.h"


CQuadTree::CQuadTree()
{
	m_sizeWorld = vector2d(CMapManager::getInstance()->getListMapInGame().at(CMapManager::getInstance()->getCurrentMapINT())->m_sizeX,
		CMapManager::getInstance()->getListMapInGame().at(CMapManager::getInstance()->getCurrentMapINT())->m_sizeY);

		m_Node = new CQuadNode(0, CBox2D(0, m_sizeWorld.y, m_sizeWorld.x, m_sizeWorld.y));
}


CQuadTree::~CQuadTree()
{
}

void CQuadTree::CreateTree()
{
	for (int i = 0; i < CMapManager::getInstance()->getListBackground().size(); ++i)
		m_Node->InsertEntity(CMapManager::getInstance()->getListBackground().at(i));
	for (int i = 0; i < CMapManager::getInstance()->getListBonus().size(); ++i)
		m_Node->InsertEntity(CMapManager::getInstance()->getListBonus().at(i));
	for (int i = 0; i < CMapManager::getInstance()->getListEnemy().size(); ++i)
		m_Node->InsertEntity(CMapManager::getInstance()->getListEnemy().at(i));
}

void CQuadTree::ReleaseTree()
{
	m_Node->ReleaseNode();

}

vector<CObjectss*>* CQuadTree::Retrieve(CBox2D rectCamera, vector<CObjectss*>* listResult)
{
	return m_Node->retrieveEntity(rectCamera, listResult);
}

