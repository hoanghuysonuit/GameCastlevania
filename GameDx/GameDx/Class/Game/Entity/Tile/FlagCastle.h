#ifndef __C_FLAG_CASTLE_H__
#define __C_FLAG_CASTLE_H__

#include "Class\Game\Entity\MovableEntity.h"

class CFlagCastle : public CMovable
{
public:
	CFlagCastle();
	~CFlagCastle();

	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;

	void setPosition(vector3d position);
	void setVelocity(vector2d velocity);
};

#endif
