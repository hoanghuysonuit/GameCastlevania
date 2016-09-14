#ifndef __SHOWBOUDING_H__
#define __SHOWBOUDING_H__

#include "Class\Game\Entity\BaseEntity.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Utill\InformationResource.h"

class CShowBouding
{
public:
	bool initEntity();
	void drawBouding(CBaseEntity* entity);
public:
	static CShowBouding*		m_instance;
	static CShowBouding*		getInstance();
private:

	CShowBouding();
	~CShowBouding();
	vector<CSprite*>			m_listSprite;
};

#endif