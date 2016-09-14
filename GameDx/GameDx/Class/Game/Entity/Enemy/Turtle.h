#ifndef __TURTULE_H__
#define __TURTULE_H__
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Utill\InformationResource.h"

class CTurtule :
	public CMovable
{
public:
	CTurtule();
	CTurtule(vector2d, int type);
	virtual ~CTurtule();

public:
	bool	initEntity();
	void	updateEntity(float deltaTime);
	void	updateEntity(CKeyBoard *device);
	void	updateEntity(RECT* rectCamera);

	void	updateCollision(float deltaTime);
	void	drawEntity();
	int		getTagNodeId();
	bool	loadSprite();

	virtual int				getObjectType()						override;

private:
	vector2d	m_Direction;
	int			m_Type;
};
#endif

