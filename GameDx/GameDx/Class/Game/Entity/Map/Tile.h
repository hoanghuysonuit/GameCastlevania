#ifndef TILE_H
#define TILE_H

#include "Class\Game\Entity\BaseEntity.h"
#include "Class\Game\Entity\StaticEntity.h"
#include "Class\Framework\Camera.h"

class CTile : public CStaticEntity
{
public:
	CTile();
	CTile(vector3d, int);
	~CTile();

public:
	virtual bool initEntity();
	virtual void updateEntity(float deltaTime);
	virtual void updateEntity(CKeyBoard* device);
	virtual void updateEntity(RECT* rectCamera);
	virtual void drawEntity();
	virtual bool loadSprite();
	virtual int  getTagNodeId();
	virtual int				getObjectType()											override;

	int    m_Index;
	vector3d  m_Pos;
	bool   isDraw;
};

#endif