#include "SitState.h"


CSitState::CSitState()
{
}


CSitState::~CSitState()
{
}

void CSitState::enter(CPlayer& player)
{
	player.setState(PLAYERSTATES::SIT);
}

CBaseState* CSitState::handleInput(CPlayer& player, CKeyBoard* device)
{
	return nullptr;
}

void CSitState::update(CPlayer& player, double deltaTime) {

}