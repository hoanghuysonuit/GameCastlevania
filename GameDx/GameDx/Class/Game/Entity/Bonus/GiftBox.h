#ifndef __CGIFTBOX_H__
#define __CGIFTBOX_H__
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Bonus\Iteminbox.h"
#include "Class\Game\Entity\Bonus\CoinInBox.h"

class CGiftBox : public CMovable
{
public:
	CGiftBox();
	CGiftBox(vector2d pos, GIFTBOX_TYPE type);
	~CGiftBox();
	virtual	bool			loadSprite()									override;
	virtual	bool			initEntity()									override;
	virtual void			updateEntity(float deltaTime)					override;
	virtual void			updateEntity(RECT* camera)                      override;
	virtual void			updateEntity(CKeyBoard *device)					override;
	virtual void			drawEntity()									override;
	virtual int				getTagNodeId()									override;
	virtual int				getObjectType()											override;
public:
	void  setPosition(vector3d);
private:
	GIFTBOX_TYPE			m_GiftBoxType;
	GIFTBOX_BRICK_EVENT		m_GiftBoxEvent;
	GIFTBOX_STATE			m_GiftBoxState;
	CIteminbox*				m_itemInBox;
	CCoinInBox*				m_Coin;
	float					GIFTBOX_PRE_POSITION_Y;
	float					GIFTBOX_PRE_POSITION_Y_MAX;
};
#endif