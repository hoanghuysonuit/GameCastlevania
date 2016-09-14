#ifndef __CBRICKMINI_H__
#define __CBRICKMINI_H__
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Bonus\CoinInBox.h"
#include "Class\Game\Entity\Bonus\Star.h"
#include "Class\Game\Entity\Bonus\GreenMushroom.h"

class CBrickMini : public CMovable
{
public:
	CBrickMini();
	CBrickMini(int map,vector3d position, BRICKMINI_TYPE type);
	~CBrickMini();
	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual int				getTagNodeId()											override;
	virtual int				getObjectType()											override;
public:
	void setPosition(vector3d position);
	void setVelocity(vector2d velocity);

private:
	int m_BrickMiniType;
	int map;
	
};
#endif