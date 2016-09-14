#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__

#include "BaseState.h"
#include "Class\Framework\CAudio.h"

class CJumpState :public CBaseState
{
public:
	CJumpState();
	~CJumpState();
	void enter(CPlayer& player);
	CBaseState* handleInput(CPlayer& player, CKeyBoard* device);
	void update(CPlayer& player, double deltaTime);
private:
	bool m_IsMoveX;
	bool m_IsJumpHigh;
	bool m_IsShoot;
	CSound* m_Sound;
};


#endif