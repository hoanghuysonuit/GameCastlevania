#ifndef __OBJECT_POOl_H__
#define __OBJECT_POOl_H__

#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Entity\BaseEntity.h"

template	<class T>	class CObjectPool
{
public:
	CObjectPool<T>() : m_IndexEntity(0){}

	T	popOverPool()
	{
		if (m_PoolObject.empty())
			return;

		T reuseableEntity		= m_PoolObject.end();
		m_PoolObject.pop_back();
		m_IndexEntity--;

		return reuseableEntity;
	}

	void pushIntoPool(T useless)
	{
		if (m_IndexEntity < LEVELPOOL(POOLSIZE))
		{
			m_PoolObject.push_back(useless);
			m_IndexEntity++;
		}
	}

protected:
	int								m_IndexEntity;
	vector<CBaseEntity*>			m_PoolObject;
};
#endif