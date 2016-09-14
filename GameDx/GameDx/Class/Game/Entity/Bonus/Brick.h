#ifndef __CBRICK_H__
#define __CBRICK_H__
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Bonus\CoinInBox.h"
#include "Class\Game\Entity\Bonus\Star.h"
#include "Class\Game\Entity\Bonus\GreenMushroom.h"
#include "Class\Game\Entity\Bonus\BrickMini.h"

class CBrick : public CMovable
{
public:
	CBrick();
	CBrick(int map,vector2d position, BRICK_TYPE type);
	~CBrick();
	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual int				getTagNodeId()											override;
	virtual int				getObjectType()											override;

public:
	int getMap();
	void setPosition(vector3d position);
	void setVelocity(vector2d velocity);

private:
	BRICK_TYPE				m_BrickType;
	GIFTBOX_BRICK_EVENT		m_BrickEvent;
	CStar*					m_Star;
	CCoinInBox*				m_Coin;
	CGreenMushroom*			m_GreenMushRoom;
	vector<CBrickMini*>		m_BrickMini;
	float					m_CountCoin;
	int						map;
	vector3d				PrePos;
};
#endif