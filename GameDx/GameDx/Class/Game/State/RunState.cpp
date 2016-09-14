#include "RunState.h"
#include "StandState.h"

CRunState::CRunState() {
	m_IsShoot = false;
}

CRunState::~CRunState() {

}

void CRunState::enter(CPlayer& player) {
	if (m_IsShoot) {
		player.setState(PLAYERSTATES::MOVE_SHOOT);
	}
	else {
		player.setState(PLAYERSTATES::RUN);
	}
}

CBaseState* CRunState::handleInput(CPlayer& player, CKeyBoard* input){
	if (!player.m_IsAutoMove){
		if (input->KeyDown(DIK_RIGHT)) {
			player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_RIGHT;
			player.setVelocity(vector2d(VEL_PLAYER_X * player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X), player.getVelocity().y));

			if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT)
			{
				player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));
			}

			if (input->KeyDown(DIK_UP) || input->KeyDown(DIK_SPACE)){
				player.m_PreJumpPos = player.getPosition();
				if (player.getVelocity().y < 0)
					player.setVelocity(vector2d(player.getVelocity().x, CHANGE_DIRECTION(player.getVelocity().y)));

				player.setVelocity(vector2d(player.getVelocity().x, player.getVelocity().y + VEL_PLAYER_Y));
				return new CJumpState();
			}

			if (input->KeyDown(DIK_P)){
				m_IsShoot = true;
			}
			else
				m_IsShoot = false;

			return this;
		}
		if (input->KeyDown(DIK_LEFT) && player.getPosition().x > 0) {
			player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_LEFT;
			player.setVelocity(vector2d(VEL_PLAYER_X * player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X), player.getVelocity().y));

			if (player.m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT)
				player.setVelocity(vector2d(CHANGE_DIRECTION(player.getVelocity().x), player.getVelocity().y));


			if (input->KeyDown(DIK_UP) || input->KeyDown(DIK_SPACE)){
				player.m_PreJumpPos = player.getPosition();
				if (player.getVelocity().y < 0)
					player.setVelocity(vector2d(player.getVelocity().x, CHANGE_DIRECTION(player.getVelocity().y)));

				player.setVelocity(vector2d(player.getVelocity().x, player.getVelocity().y + VEL_PLAYER_Y));
				return new CJumpState();
			}

			if (input->KeyDown(DIK_P)){
				m_IsShoot = true;
			}
			else
				m_IsShoot = false;

			return this;
		}

		return new CStandState();
	}
	else {
		if (player.getVelocity().x == 0) {
			player.setVelocity(vector2d(VEL_PLAYER_X, player.getVelocity().y));
			}
		return this;
	}
}

void CRunState::update(CPlayer& player, double deltaTime) {
	if (player.m_IsCollision) {
		player.setVelocity(vector2d(VEL_PLAYER_X_MIN, player.getVelocity().y));
	}

	if (player.m_IsAutoMove) {
		// If position x of player at the castle (350), stop running auto
		if (player.getPosition().x > 3232) {
			player.m_IsAutoMove = false;
		}
		//player.setPosition(vector3d(player.getPosition().x + player.getVelocity().x * deltaTime / 120, player.getPosition().y + player.getVelocity().y * deltaTime / 100, 0));
	}
		player.setPosition(vector3d(player.getPosition().x + player.getVelocity().x * deltaTime / 120, player.getPosition().y + (player.getVelocity().y + GRAVITATION) * deltaTime / 100, 0));


}
