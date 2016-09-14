#include "ClimbState.h"


CClimbState::CClimbState() {

}

CClimbState::~CClimbState() {

}

void CClimbState::enter(CPlayer& player) {
	player.setState(PLAYERSTATES::CLIMB);
}

CBaseState* CClimbState::handleInput(CPlayer& player, CKeyBoard* input) {
	return this;
}

void CClimbState::update(CPlayer& player, double deltaTime) {
	if (player.getPosition().y > 90)
		player.setVelocity(vector2d((float)VEL_PLAYER_X, VEL_PLAYER_Y_MIN));

	if (player.m_IsAutoMove == false)
		player.setPosition(vector3d(player.getPosition().x, player.getPosition().y + (player.getVelocity().y + GRAVITATION) * deltaTime / 240, 0));
}