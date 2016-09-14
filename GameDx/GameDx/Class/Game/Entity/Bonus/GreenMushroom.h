#ifndef __CGREENMUSHROOM_H__
#define __CGREENMUSHROOM_H__
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Player\Player.h"

class CGreenMushroom : public CMovable
{
public:
	CGreenMushroom();
	CGreenMushroom(vector3d pos);
	~CGreenMushroom();
	virtual bool			loadSprite()									override;
	virtual	bool			initEntity()									override;
	virtual void			updateEntity(float deltaTime)					override;
	virtual void			updateEntity(RECT* camera)                      override;
	virtual void			updateEntity(CKeyBoard *device)					override;
	virtual void			drawEntity()									override;
	virtual int				getTagNodeId()									override;
	virtual int				getObjectType()									override;
public:
	void setVelocity(vector2d velocity);
private:
	float m_Pos_y_Max;
};
#endif