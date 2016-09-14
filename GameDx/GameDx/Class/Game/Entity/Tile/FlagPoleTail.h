#ifndef __C_FLAG_POLE_TAIL_H__
#define __C_FLAG_POLE_TAIL_H__

#include "Class\Game\Entity\StaticEntity.h"

class CFlagPoleTail : public CStaticEntity
{
public:
	CFlagPoleTail();
	CFlagPoleTail(vector2d pos);
	~CFlagPoleTail();

	virtual bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)								override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual int				getTagNodeId()											override;
	virtual void			drawEntity()											override;
	virtual bool			loadSprite()											override;
	virtual	int				getObjectType()											override;
private:

};

#endif