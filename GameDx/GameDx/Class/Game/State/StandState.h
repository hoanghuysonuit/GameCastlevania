#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__

#include "BaseState.h"
#include "RunState.h"
#include "JumpState.h"

class CStandState : public CBaseState {
public:
	CStandState();
	CStandState(vector3d);
	~CStandState();
	void enter(CPlayer& player);
	CBaseState* handleInput(CPlayer& player, CKeyBoard* device);
	void update(CPlayer& player, double deltaTime);
private:
	bool m_IsShoot;
};

#endif