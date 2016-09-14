#include "DieState.h"

CDieState::CDieState() {
}

CDieState::~CDieState() {

}

void CDieState::enter(CPlayer& player) {
	player.setState(PLAYERSTATES::DIE);
}

CBaseState* CDieState::handleInput(CPlayer& player, CKeyBoard* input){

	return this;
}

void CDieState::update(CPlayer& player, double deltaTime) {

	player.setPosition(vector3d(player.getPosition().x, player.getPosition().y + (player.getVelocity().y + GRAVITATION) * deltaTime / 60, 0));
}