#include "JumpState.h"
#include "StandState.h"

CJumpState::CJumpState() {
	m_IsMoveX = false;
	m_IsJumpHigh = false;
	m_IsShoot = false;

	if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::SMALL)
	{
		m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_jump-small.wav");
	}
	 else if (CPlayer::getInstance()->getPlayerTag() == PLAYERTAGS::BIG)
	{
		m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//smb_jump-super.wav");
	}
}

CJumpState::~CJumpState() {
	SAFE_RELEASE(this->m_Sound);

}

void CJumpState::enter(CPlayer& player) {
	if (m_IsShoot)
	{
		player.setState(PLAYERSTATES::JUMP_SHOOT);
	}
	else {
		player.setState(PLAYERSTATES::JUMP);
	}
}

CBaseState* CJumpState::handleInput(CPlayer& player, CKeyBoard* input) {
	if (input->KeyDown(DIK_SPACE)) {
		m_IsJumpHigh = true;
	}

	if (input->KeyDown(DIK_P)){
		m_IsShoot = true;
	}
	else
		m_IsShoot = false;

	if (input->KeyDown(DIK_RIGHT)) {
		player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_RIGHT;
		m_IsMoveX = true;
		if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT)
			player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));

		return this;
	}
	else if (input->KeyDown(DIK_LEFT)) {
		player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_LEFT;
		m_IsMoveX = true;
		if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT)
			player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));
		return this;
	}
	return this;
}

void CJumpState::update(CPlayer& player, double deltaTime){

	//CAudio::getInstance()->PlaySoundW(m_Sound);
	double deltaX = 0;

	//if (player.m_IsAutoJump && player.getStateInt() != PLAYERSTATES::DIE) {
	//	m_IsMoveX = true;
	//	player.m_IsAutoJump = false;
	//}

	if (m_IsMoveX) {

		if (player.getVelocity().x == VEL_PLAYER_X_MIN)
		{
			player.setVelocity(vector2d(VEL_PLAYER_X * player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X), player.getVelocity().y));
		}
		deltaX = player.getVelocity().x * deltaTime / 60;
	}

	if (m_IsJumpHigh) {
		if (player.getPosition().y >= player.m_PreJumpPos.y + PLAYER_JUMP_HIGH_LIMIT)
			player.setVelocity(vector2d(player.getVelocity().x, VEL_PLAYER_Y_MIN));
	}
	else {
		if (player.getPosition().y >= player.m_PreJumpPos.y + PLAYER_JUMP_LIMIT)
			player.setVelocity(vector2d(player.getVelocity().x, VEL_PLAYER_Y_MIN));
	}

	player.setPosition(vector3d(player.getPosition().x + deltaX, player.getPosition().y + (player.getVelocity().y + GRAVITATION) *deltaTime / 40, 0));
}