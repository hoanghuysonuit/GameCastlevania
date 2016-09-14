#ifndef __C_FLAG_POLE_HEAD_H__
#define __C_FLAG_POLE_HEAD_H__

#include "Class\Game\Entity\StaticEntity.h"

class CFlagPoleHead : public CStaticEntity
{
public:
	CFlagPoleHead();
	CFlagPoleHead(vector2d pos);
	~CFlagPoleHead();

	virtual bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)								override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual bool			loadSprite()											override;
private:

};

#endif