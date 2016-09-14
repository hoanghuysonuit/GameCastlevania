#ifndef __C_CASTLE_H__
#define __C_CASTLE_H__

#include "Class\Game\Entity\StaticEntity.h"

class CCastle : public CStaticEntity
{
public:
	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	CCastle();
	~CCastle();
};

#endif
