#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Algorithsm\Singleton.h"
#include "Class\Game\Algorithsm\QuadNode.h"

class CQuadTree : public CSingleton<CQuadTree>
{
public:
	CQuadTree();
	CQuadTree(int level, CBox2D* bound);
	~CQuadTree();

	int level;
	vector<CObjectss*> listObjects;
	CQuadTree** nodes;
	CBox2D* bounds;

	void								CreateTree();
	void								ReleaseTree();
	vector<CObjectss*>*					Retrieve(CBox2D, vector<CObjectss*>*);
protected:
	CQuadNode*							m_Node;
	vector2d							m_sizeWorld;
};

#endif

