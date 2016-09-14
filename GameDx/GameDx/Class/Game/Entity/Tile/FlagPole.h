#ifndef __C_FLAG_POLE_H__
#define __C_FLAG_POLE_H__

#include "Class\Game\Entity\StaticEntity.h"

class CFlagPole : public CStaticEntity
{
public:
	CFlagPole();
	CFlagPole(vector2d pos);
	~CFlagPole();

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