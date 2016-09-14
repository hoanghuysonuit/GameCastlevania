#include "BaseState.h"

void CBaseState::exitCurrentState(CPlayer& player, CBaseState* newState) {
	if (player.getState() != nullptr) {
		delete player.getState();
		player.setState(newState);
	}
}