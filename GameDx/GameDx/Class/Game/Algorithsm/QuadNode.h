#ifndef __QUADNODE_H__
#define __QUADNODE_H__

#include "Class\Mathematics\Box2D.h"
#include "Class\Game\Utill\stdafx.h"	
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Entity\BaseEntity.h"

class CQuadNode
{
public:
	CQuadNode();
	CQuadNode(int Level, CBox2D NodeBound);
	~CQuadNode();

	void					ReleaseNode();
	bool					InsertEntity(CObjectss*);

	int						getNodeLevel();							void		setNodeLevel(int);
	CBox2D					getNodeSize();							void		setNodeSize(CBox2D);
	vector<CObjectss*>*		retrieveEntity(CBox2D, vector<CObjectss*>*);
	vector<CObjectss*>		getEntityList();						
	CQuadNode**				getParent();							
	void					SplitParent();

private:
	int						m_NodeLevel;
	CBox2D					m_NodeSize;
	vector<CObjectss*>		m_EntityList;
	CQuadNode**				m_Node;
};

#endif