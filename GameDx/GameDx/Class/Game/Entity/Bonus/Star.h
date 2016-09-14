#ifndef __CSTAR_H__
#define __CSTAR_H__
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Player\Player.h"

class CStar : public CMovable
{
public:
	CStar();
	CStar(vector3d pos);
	~CStar();
	virtual	bool			loadSprite()									override;
	virtual	bool			initEntity()									override;
	virtual void			updateEntity(float deltaTime)					override;
	virtual void			updateEntity(RECT* camera)                      override;
	virtual void			updateEntity(CKeyBoard *device)					override;
	virtual void			drawEntity()									override;		
	virtual int				getTagNodeId()									override;
	virtual int				getObjectType()									override;

private:
	float STAR_POSITION_Y_MAX;
};
#endif