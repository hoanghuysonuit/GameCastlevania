#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Framework\Camera.h"
#include "Class\Game\Algorithsm\Singleton.h"
#include "Class\Game\Utill\ShowBouding.h"

#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__


class Elevator : public CMovable
{
public:
	Elevator();
	Elevator(vector2d pos, ELEVATOR_STATE ElevatorState);
	~Elevator();

	virtual bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)								override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual bool			loadSprite()											override;
	virtual int				getTagNodeId()											override;
	virtual int				getObjectType()											override;

protected:
	vector2d				m_Acceleration;
	int						m_Type;
	float					ELEVATOR_POSITION_Y_MIN;
	float					ELEVATOR_POSITION_Y_MAX;
};
#endif
