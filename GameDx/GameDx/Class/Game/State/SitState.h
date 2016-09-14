#ifndef __C_SIT_STATE_H__
#define __C_SIT_STATE_H__

#include "BaseState.h"

class CSitState: public CBaseState
{
public:
	CSitState();
	~CSitState();
	void enter(CPlayer& player);
	CBaseState* handleInput(CPlayer& player, CKeyBoard* device);
	void update(CPlayer& player, double deltaTime);
};

#endif

