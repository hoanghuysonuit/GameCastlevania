#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__

#include "Class\Game\Entity\Player\Player.h"


class CBaseState
{
public:
	virtual ~CBaseState(){};
	virtual void enter(CPlayer& player) {};
	virtual CBaseState* handleInput(CPlayer& player, CKeyBoard* device){ return nullptr;};
	virtual void update(CPlayer& player, double deltaTime){};
	virtual void update(CPlayer& player, CBaseEntity* entity) {};
	void exitCurrentState(CPlayer& player, CBaseState* newState);
};
#endif