#ifndef __CCOIN_H__
#define __CCOIN_H__
#include "Class\Game\Entity\StaticEntity.h"
#include "Class\Game\Entity\Player\Player.h"

class CCoin : public CStaticEntity
{
public:
	CCoin();

	CCoin(LPDIRECT3DDEVICE9);
	CCoin(vector2d newPosition);

	~CCoin();
	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual int             getTagNodeId()											override;
	virtual int				getObjectType()											override;

};
#endif