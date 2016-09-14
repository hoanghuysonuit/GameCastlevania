#ifndef __C_FLAG_H__
#define __C_FLAG_H__

#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Framework\Camera.h"

class CFlag : public CMovable
{
public:
	CFlag();
	CFlag(vector2d pos);
	~CFlag();
	virtual bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)								override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual int				getTagNodeId()											override;
	virtual bool			loadSprite()											override;
	virtual	int				getObjectType()											override;
private:
};

#endif