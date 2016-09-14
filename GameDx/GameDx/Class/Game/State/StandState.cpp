#include "StandState.h"
#include "DieState.h"

CStandState::CStandState() {
	m_IsShoot = false;
	//CPlayer::getInstance()->setVelocity(vector2d(CPlayer::getInstance()->getVelocity().x, VEL_DEFAULT_Y));
}

CStandState::CStandState(vector3d newPos) {
	CPlayer::getInstance()->setPosition(newPos);
	m_IsShoot = false;
}

CStandState::~CStandState() {

}

void CStandState::enter(CPlayer& player) {
	//player.setVelocity(vector2d(VEL_PLAYER_X_MIN, player.getVelocity().y));
	if (m_IsShoot)
	{
		player.setState(PLAYERSTATES::STAND_SHOOT);
	}
	else
	{
		player.setState(PLAYERSTATES::STAND);
	}
}

CBaseState* CStandState::handleInput(CPlayer& player, CKeyBoard* input){

	if (input->KeyDown(DIK_RIGHT)) {
		if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT)
			player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));
		else
			player.setVelocity(vector2d(VEL_PLAYER_X, player.getVelocity().y));

		return new CRunState();
	}

	if (input->KeyDown(DIK_LEFT)) {
		if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT)
			player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));
		return new CRunState();
	}

	if (input->KeyPress(DIK_UP) || input->KeyDown(DIK_SPACE) || player.m_IsAutoJump == true){
		player.m_PreJumpPos = player.getPosition();
		if (player.getVelocity().y < 0)
			player.setVelocity(vector2d(player.getVelocity().x, CHANGE_DIRECTION(player.getVelocity().y)));

		player.setVelocity(vector2d(player.getVelocity().x, player.getVelocity().y + VEL_PLAYER_Y));

		return new CJumpState();
	}

	if (input->KeyDown(DIK_P)){
		m_IsShoot = true;
		return this;
	}
	else
		m_IsShoot = false;
	return nullptr;
}

void CStandState::update(CPlayer& player, double deltaTime) {
	if (!player.m_IsAutoMove)
		player.setVelocity(vector2d(VEL_PLAYER_X_MIN, player.getVelocity().y));
	else {
		this->exitCurrentState(player, new CRunState());
		player.getState()->enter(player);
	}

	player.setPosition(vector3d(player.getPosition().x, player.getPosition().y + (player.getVelocity().y + GRAVITATION) * deltaTime / 60, 0));
}