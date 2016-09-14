#ifndef __OBTS_H__
#define __OBTS_H__
#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Framework\Sprite.h"
#include "Class\Game\Utill\ResourceManager\BaseResource.h"
#include "Class\Mathematics\Box2D.h"

class CObjectss
{
public:
	CObjectss();
	virtual ~CObjectss() = 0;

	virtual bool			initEntity()					= 0;
	virtual bool			loadSprite()					= 0;
	virtual void			updateEntity(float deltaTime)	= 0;
	virtual void			drawEntity()					= 0;

	virtual CBox2D			getBounding()					= 0;
	virtual const char*		getTagNode()					= 0;
	virtual vector3d		getPosition()					= 0;
	virtual int				getObjectType()					= 0;

	virtual int				getTagNodeId()          { return 0; };

	bool					isDestroy;
protected:
	const char*				m_TagNode;
	vector3d				m_Position;
	vector<CSprite*>		m_listSprite;

	CBaseResource*			m_ResouceImage;
	CBox2D*					m_Bounding;
	int						m_State;

};

#endif