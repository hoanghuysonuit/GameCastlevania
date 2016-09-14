/****************************************************************************/
/* Create by Michael Le AND Shin Truong*/
/* 08/07/2015 */
/***************************************************************************/

#ifndef CMOVABLE__H
#define CMOVABLE__H

#include "BaseEntity.h"
#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Mathematics\Box2D.h"


class CMovable : public CBaseEntity
{
public:
	CMovable();
	virtual ~CMovable();
	virtual  bool			loadSprite() = 0;
	virtual  vector3d		getPosition();
	virtual  CBox2D			getBounding()											override;
	virtual  bool			initEntity();
	virtual  const char*    getTagNode()											override;
	virtual int				getObjectType()											override { return 0; };
	virtual  int			getTagNodeId()											override { return 0; };
	virtual  vector2d		getVelocity();
	virtual  void			setVelocity(vector2d);


protected:
	vector2d    m_Velocity;
};

#endif