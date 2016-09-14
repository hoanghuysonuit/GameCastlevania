#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__

#include "BaseState.h"

class CClimbState : public CBaseState
{
public:
	CClimbState();
	void enter(CPlayer& player);
	CBaseState* handleInput(CPlayer& player, CKeyBoard* device);
	void update(CPlayer& player, double deltaTime);
	~CClimbState();
private:
};


#endif