#include "QuadNode.h"

CQuadNode::CQuadNode()
{
	m_NodeLevel = 0;
	m_NodeSize	= CBoxZero;
}

CQuadNode::~CQuadNode()
{
}

CQuadNode::CQuadNode(int Level, CBox2D NodeBound)
{
	m_NodeLevel		= Level;
	m_NodeSize		= NodeBound;
}

int CQuadNode::getNodeLevel()
{
	return m_NodeLevel;
}

void CQuadNode::setNodeLevel(int Level)
{
	m_NodeLevel = Level;
}

CBox2D CQuadNode::getNodeSize()
{
	return m_NodeSize;
}

void CQuadNode::setNodeSize(CBox2D Size)
{
	m_NodeSize = Size;
}

CQuadNode** CQuadNode::getParent()
{
	return m_Node;
}

void CQuadNode::SplitParent()
{
	m_Node = new CQuadNode*[4];

	this->m_Node[0] = new CQuadNode(this->m_NodeLevel * 10 + 1, CBox2D(this->m_NodeSize.getX(),										this->m_NodeSize.getY(),									this->m_NodeSize.getWidth() / 2, this->m_NodeSize.getHeight() / 2));
	this->m_Node[1] = new CQuadNode(this->m_NodeLevel * 10 + 2, CBox2D(this->m_NodeSize.getX() + this->m_NodeSize.getWidth() / 2,	this->m_NodeSize.getY(),									this->m_NodeSize.getWidth() / 2, this->m_NodeSize.getHeight() / 2));
	this->m_Node[2] = new CQuadNode(this->m_NodeLevel * 10 + 3, CBox2D(this->m_NodeSize.getX(),										this->m_NodeSize.getY() - this->m_NodeSize.getHeight() / 2, this->m_NodeSize.getWidth() / 2, this->m_NodeSize.getHeight() / 2));
	this->m_Node[3] = new CQuadNode(this->m_NodeLevel * 10 + 4, CBox2D(this->m_NodeSize.getX() + this->m_NodeSize.getWidth() / 2,	this->m_NodeSize.getY() - this->m_NodeSize.getHeight() / 2,	this->m_NodeSize.getWidth() / 2, this->m_NodeSize.getHeight() / 2));
}

vector<CObjectss*> CQuadNode::getEntityList()
{
	return m_EntityList;
}

void CQuadNode::ReleaseNode()
{
	CObjectss* objTemp;

	if (!m_Node)
	for (int i = 0; i < 4; ++i)
	{
		m_Node[i]->ReleaseNode();
	}
	for (int i = 0; i < m_EntityList.size(); ++i)
	{
		objTemp = m_EntityList.back();
		m_EntityList.pop_back();
		delete objTemp;
	}

	SAFE_RELEASE(m_Node);
}

bool CQuadNode::InsertEntity(CObjectss* entity)
{
	if (m_Node)
	{
		if (CBox2D::Intersect(m_Node[0]->getNodeSize(), entity->getBounding()))
			m_Node[0]->InsertEntity(entity);
		if (CBox2D::Intersect(m_Node[1]->getNodeSize(), entity->getBounding()))
			m_Node[1]->InsertEntity(entity);
		if (CBox2D::Intersect(m_Node[2]->getNodeSize(), entity->getBounding()))
			m_Node[2]->InsertEntity(entity);
		if (CBox2D::Intersect(m_Node[3]->getNodeSize(), entity->getBounding()))
			m_Node[3]->InsertEntity(entity);
	}

	else if(CBox2D::Intersect(this->getNodeSize(), entity->getBounding()))
		m_EntityList.push_back(entity);

	if (m_EntityList.size() > MAX_OBJECT_OF_NODE && m_NodeLevel < MAX_LEVEL_OF_NODE)
	{
		this->SplitParent();

		while (!m_EntityList.empty())
		{
			if (CBox2D::Intersect(m_Node[0]->getNodeSize(), m_EntityList.back()->getBounding()))
				m_Node[0]->InsertEntity(m_EntityList.back());
			if (CBox2D::Intersect(m_Node[1]->getNodeSize(), m_EntityList.back()->getBounding()))
				m_Node[1]->InsertEntity(m_EntityList.back());
			if (CBox2D::Intersect(m_Node[2]->getNodeSize(), m_EntityList.back()->getBounding()))
				m_Node[2]->InsertEntity(m_EntityList.back());
			if (CBox2D::Intersect(m_Node[3]->getNodeSize(), m_EntityList.back()->getBounding()))
				m_Node[3]->InsertEntity(m_EntityList.back());

			m_EntityList.pop_back();
		}
	}
	return true;
}

vector<CObjectss*>* CQuadNode::retrieveEntity(CBox2D rectCamera, vector<CObjectss*>* listResult)
{
	if (m_Node != NULL)
	{
		m_Node[0]->retrieveEntity(rectCamera, listResult);
		m_Node[1]->retrieveEntity(rectCamera, listResult);
		m_Node[2]->retrieveEntity(rectCamera, listResult);
		m_Node[3]->retrieveEntity(rectCamera, listResult);
	}
	else
	for (int i = 0; i < m_EntityList.size(); ++i)
		if (m_EntityList.at(i)->isDestroy)
			m_EntityList.erase(m_EntityList.begin() + i);

	if (CBox2D::Intersect(this->getNodeSize(), rectCamera) && (!m_EntityList.empty()))
	{
		int temp = 1;
		for (int i = 0; i < m_EntityList.size(); ++ i)
			listResult->push_back(m_EntityList.at(i));
	}

	return listResult;
};
