/****************************************************************************/
/* Create by Michael Le*/
/* 08/07/2015 */
/***************************************************************************/


#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Framework\KeyBoard.h"
#include "Class\Mathematics\Box2D.h"
#include "Class\Framework\Sprite.h"
#include "Class\Framework\Camera.h"
#include "Class\Game\Entity\Objectss.h"
#include "Class\Game\Utill\ResourceManager\BaseResource.h"

class CBaseEntity : public CObjectss
{
public:

	CBaseEntity();
	CBaseEntity(directDevice);
	virtual ~CBaseEntity();


	virtual void				updateEntity(CKeyBoard* deivce)							= 0;
	virtual void				updateEntity(RECT* camera)								= 0;
	virtual void				updateEntity(float deltaTime)							= 0;
	virtual const char*			getTagNode()											= 0;
	virtual vector2d			getVelocity()											= 0;
	virtual vector3d			getPosition()											= 0;
	virtual int					getTagNodeId()          { return 0; };
	virtual int					getObjectType() = 0;


	bool m_IsEnable;

protected:

protected:
	vector2d    m_Velocity;


};


#endif