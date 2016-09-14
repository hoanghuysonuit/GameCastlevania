#ifndef __TILESS_H__
#define __TILESS_H__
#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Entity\Objectss.h"
#include "Class\Framework\Camera.h"

class CTiless : public CObjectss
{
public:
	CTiless();
	CTiless(vector2d, int type);
	~CTiless();

	virtual		bool			initEntity();
	virtual		void			drawEntity();
	virtual		bool			loadSprite();
	virtual		CBox2D			getBounding()			override;
	virtual const char*			getTagNode()			override;
	virtual		void			updateEntity(float deltaTime){};
	virtual int					getObjectType()			override;
	virtual int					getTagNodeId()          override;
	virtual vector3d			getPosition()			override;
private:
	int				m_ID;
};

#endif