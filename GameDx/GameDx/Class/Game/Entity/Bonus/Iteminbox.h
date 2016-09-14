#ifndef __CITEMINBOX_H__
#define __CITEMINBOX_H__
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Framework\CAudio.h"

class CIteminbox : public CMovable
{
public:
	CIteminbox();
	CIteminbox(vector2d pos);
	~CIteminbox();
	virtual bool			loadSprite()									override;
	virtual	bool			initEntity()									override;
	virtual void			updateEntity(float deltaTime)					override;
	virtual void			updateEntity(RECT* camera)                      override;
	virtual void			updateEntity(CKeyBoard *device)					override;
	virtual void			drawEntity()									override;
	virtual int             getTagNodeId()									override;
	virtual int				getObjectType()											override;

public:
	void chkShowItem(CPlayer*);
	void setVelocity(vector2d velocity);
	void setPosition(vector3d position);
	ITEMINBOX_TYPE getItemType();

private:
	ITEMINBOX_TYPE        m_itemtype;
	float				  ITEMINBOX_POSITION_Y_MAX;
	CSound*				  m_Sound1;
	CSound*				  m_Sound2;
};
#endif