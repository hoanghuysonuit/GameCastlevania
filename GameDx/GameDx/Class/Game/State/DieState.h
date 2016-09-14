#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__

#include "BaseState.h"
#include "RunState.h"
#include "JumpState.h"

class CDieState : public CBaseState {
public:
	CDieState();
	~CDieState();
	void enter(CPlayer& player);
	CBaseState* handleInput(CPlayer& player, CKeyBoard* device);
	void update(CPlayer& player, double deltaTime);
private:
};

#endif