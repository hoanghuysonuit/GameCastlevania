#ifndef __CCOININBOX_H__
#define __CCOININBOX_H__
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Framework\CAudio.h"

class CCoinInBox : public CMovable
{
public:
	CCoinInBox();
	CCoinInBox(vector3d pos);
	~CCoinInBox();
	virtual	bool			loadSprite()											override;
	virtual	bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)                              override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual int				getTagNodeId()											override;
	virtual int				getObjectType()											override;
private:
	bool isDraw;
	CSound* m_Sound;
	float   m_Pos_y_Max;
	float	m_Pos_y_Min;
};
#endif