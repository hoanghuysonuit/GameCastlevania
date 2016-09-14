#include "Player.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Game\State\StandState.h"
#include "Class\Game\State\DieState.h"
#include "Class\Game\State\ClimbState.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\State\DieState.h"
#include "Class\\Game\Entity\Map\MapManager.h"
#include "Class\Game\Scene\PopupInfo.h"

inline bool IsCollision_Player(CMovable* entity, vector<CBaseEntity*> listEntity) {
	for (int i = 0; i < listEntity.size(); i++)
	{
		if (listEntity.at(i)->getTagNodeId() == TAGNODE::BRICK || listEntity.at(i)->getTagNodeId() == TAGNODE::GIFT_BOX)
		{
			if (CCollision::CheckCollision(entity, listEntity.at(i)) == COLDIRECTION::COLDIRECTION_TOP)
			{
				return true;
			}
		}
	}

	return false;
}

inline bool IsCollision_WithRect(CMovable* entity, vector<CBox2D*> listEntity) {
	for (int i = 0; i < listEntity.size(); i++)
	{
		entity->getBounding().setVelocity(entity->getVelocity());
		if (CCollision::CheckCollision(entity->getBounding(), *listEntity.at(i)))
		{
			return true;
		}

	}

	return false;
}

CPlayer::CPlayer()
{
	this->initEntity();
}

CPlayer::~CPlayer()
{
	SAFE_RELEASE(m_PlayerState);
	SAFE_RELEASE(m_ResouceImage);
	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

CPlayer::CPlayer(directDevice device)
{
	this->initEntity();

}

bool CPlayer::initEntity()
{
	m_IsCollision = false;
	m_IsAutoMove = false;
	m_IsAutoJump = false;
	m_IsFreeFall = false;
	m_Direction.push_back(DIRECTION::DIRECTION_NONE);
	m_Direction.push_back(DIRECTION::DIRECTION_NONE);

	m_UndyingTime = 0;
	m_Position = vector3d(50, 70, 0);
	m_PreJumpPos = vector3d(0, 0, 0);

	m_State = PLAYERSTATES::STAND;
	m_PlayerState = new CStandState();
	m_PlayerTag = PLAYERTAGS::SMALL;

	m_Acceleration = vector2d(0.5f, 0);
	m_Velocity = vector2d(VEL_PLAYER_X_MIN, VEL_DEFAULT_Y);

	m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_RIGHT;
	m_Direction.at(DIRECTIONINDEX::DIRECTION_Y) = DIRECTION::DIRECTION_UP;

	this->m_ResouceImage = new CPlayerResource(TAGNODE::PLAYER);
	this->loadSprite();
	this->m_Bounding = new CBox2D(0, 0, 0, 0);

	return true;
}

int	CPlayer::getTagNodeId() {
	return TAGNODE::PLAYER;
}

bool CPlayer::loadSprite()
{
	if (m_listSprite.size() > 0) {
		m_listSprite.clear();
	}

	switch (m_PlayerTag)
	{
	case PLAYERTAGS::SMALL:
		//	push_back_new<CSprite>(m_listSprite);

		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::RUN), 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::JUMP), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::DIE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL, PLAYERSTATES::CLIMB), 1, 2, 2, 0));
		break;
	case PLAYERTAGS::BIG:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::RUN), 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::JUMP), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::DIE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::CLIMB), 1, 2, 2, 0));
		break;
	case PLAYERTAGS::SMALL_UNDYING:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL_UNDYING, PLAYERSTATES::STAND), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL_UNDYING, PLAYERSTATES::STAND), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL_UNDYING, PLAYERSTATES::RUN), 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL_UNDYING, PLAYERSTATES::JUMP), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::SMALL_UNDYING, PLAYERSTATES::DIE), 1, 1, 1, 0));
		//this->m_listSprite.push_back(new CSprite(CInfomationResource::smallmario_climb, 1, 2, 2, 0));
		break;
	case PLAYERTAGS::UNDYING:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::UNDYING, PLAYERSTATES::STAND), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::UNDYING, PLAYERSTATES::STAND), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::UNDYING, PLAYERSTATES::RUN), 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::UNDYING, PLAYERSTATES::JUMP), 1, 4, 4, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::UNDYING, PLAYERSTATES::DIE), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::BIG, PLAYERSTATES::CLIMB), 1, 2, 2, 0));

		//	this->m_listSprite.push_back(new CSprite(CInfomationResource::bigmario_climb, 1, 2, 2, 0));
		break;
	case PLAYERTAGS::FIRE:
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::STAND), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::RUN), 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::JUMP), 1, 1, 1, 0));
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::DIE), 1, 1, 1, 0));
		/*this->m_listSprite.push_back(new CSprite(CInfomationResource::bigfiremario_runfire, 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(CInfomationResource::bigfiremario_runfire, 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(CInfomationResource::bigfiremario_runfire, 1, 3, 3, 0));
		this->m_listSprite.push_back(new CSprite(CInfomationResource::bigfiremario_jumfire, 1, 1, 1, 0));*/
		this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(PLAYERTAGS::FIRE, PLAYERSTATES::CLIMB), 1, 2, 2, 0));
		break;
	default:
		break;
	}

	return true;
}

void CPlayer::updateEntity(float deltaTime)
{
	if (this->m_PlayerTag == PLAYERTAGS::UNDYING)
	{
		if (m_UndyingTime >= 0)
			m_UndyingTime -= deltaTime;
		else
		{
			this->m_PlayerTag = m_PreTag;
			this->loadSprite();
		}
	}

	else if (this->m_PlayerTag == PLAYERTAGS::SMALL_UNDYING)
	{
		if (m_UndyingTime >= 0)
			m_UndyingTime -= deltaTime;
		else
		{
			this->m_PlayerTag = PLAYERTAGS::SMALL;
			this->loadSprite();
		}
	}

	if (m_PlayerState)
		m_PlayerState->update(*this, deltaTime);

}

void CPlayer::updateEntity(RECT* camera) {

}

void CPlayer::updateEntity(CKeyBoard* input)
{
	if (input->KeyPress(DIK_F1))
	if (CMapManager::getInstance()->getCurrentMapINT() == 1)
		m_Position = vector3d(3180, 50, 0);
	else if (CMapManager::getInstance()->getCurrentMapINT() == 2)
		m_Position = vector3d(3819, 50, 0);

	if (m_PlayerState){
		CBaseState* state = m_PlayerState->handleInput(*this, input);

		if (state != nullptr)
		{
			if (m_PlayerState != state)
				delete m_PlayerState;
			m_PlayerState = state;
		}
		m_PlayerState->enter(*this);
	}
}

void CPlayer::handleCollisionWithTile(float deltaTime) {

	vector<CBox2D*> listRect = CMapManager::getInstance()->getListRect();

	for (int i = 0; i < listRect.size(); ++i) {
		if (this->m_State != PLAYERSTATES::DIE) {

			this->getBounding().setVelocity(this->getVelocity());

			switch (CCollision::CheckCollision(this->getBounding(), *(listRect.at(i))))
			{
			case COLDIRECTION::COLDIRECTION_TOP:
				m_IsFreeFall = false;
				m_IsAutoJump = false;
				m_Velocity.y = VEL_DEFAULT_Y;

				this->m_Position.y = listRect.at(i)->getY() + this->getBounding().getHeight() / 2;

				if (!m_IsAutoMove) {
					if (this->m_State != PLAYERSTATES::RUN && this->m_State != PLAYERSTATES::MOVE_SHOOT) {
						this->m_PlayerState->exitCurrentState(*this, new CStandState());
						this->m_PlayerState->enter(*this);
					}
				}
				else {
					this->m_PlayerState->exitCurrentState(*this, new CRunState());
					this->m_PlayerState->enter(*this);
				}

				break;
			case COLDIRECTION::COLDIRECTION_NONE:
				if (m_State != PLAYERSTATES::JUMP) {
					if (!IsCollision_WithRect(this, listRect)){
						m_Velocity.y = VEL_PLAYER_Y_MIN;
						m_IsFreeFall = true;
					}

				}

				break;

			case COLDIRECTION::COLDIRECTION_BOTTOM:
				this->m_Position.y = listRect.at(i)->getY() - listRect.at(i)->getHeight() - this->getBounding().getHeight() / 2;
				if (this->m_Velocity.y >= 0)
				{
					//this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);
					this->m_Velocity.y = VEL_PLAYER_Y_MIN;
				}
				break;
			case COLDIRECTION::COLDIRECTION_LEFT:
				if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT) {
					m_Position.x = listRect.at(i)->getX() - this->getBounding().getWidth() / 2;
					m_Velocity.x = VEL_PLAYER_X_MIN;

					if (m_IsAutoJump) {
						m_Velocity.y = VEL_PLAYER_Y_MIN;
					}
				}
				else if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT) {
					m_Velocity.x = -VEL_PLAYER_X;
				}
				break;
			case COLDIRECTION::COLDIRECTION_RIGHT:
				if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT) {
					m_Velocity.x = VEL_PLAYER_X_MIN;
					m_Position.x = listRect.at(i)->getX() + listRect.at(i)->getWidth() + this->getBounding().getWidth() / 2;

				/*	if (m_IsAutoJump) {
						m_Velocity.y = VEL_PLAYER_Y_MIN;
					}*/
				}
				else if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT) {
					m_Velocity.x = VEL_PLAYER_X;
				}
				break;
			default:

				break;
			}

			//}
		}
		else
		{
			if (m_Position.y >= 100 && m_Velocity.y >= 0){
				m_Velocity.y = CHANGE_DIRECTION(m_Velocity.y);
			}

		}

	}

	//-----Handle Collision with Screen - Die State----//

	this->getBounding().setVelocity(this->getVelocity());
	if (CCollision::CheckCollision(this->getBounding(), CBox2D(0, 0, 3584, 0)) == COLDIRECTION::COLDIRECTION_TOP) {
		if (!m_IsAutoMove && !m_IsAutoJump && m_State != PLAYERSTATES::DIE){
			m_Velocity.y = VEL_DEFAULT_Y + VEL_PLAYER_Y;
			m_IsFreeFall = false;
			this->m_PlayerState->exitCurrentState(*this, new CDieState());
			this->m_PlayerState->enter(*this);
		}
	}
}

void CPlayer::handleCollisionWithBonus(CObjectss* bonusEntity, float deltaTime) {

	//-----Handle Collision with Bonus----//
	switch (bonusEntity->getTagNodeId())
	{
	case TAGNODE::RED_MUSHROOM:
		if (CCollision::CheckCollision(this, bonusEntity)) {
			if (this->m_PlayerTag == PLAYERTAGS::SMALL) {
				m_PlayerTag = PLAYERTAGS::BIG;
				this->loadSprite();
			}
		}
		break;
	case TAGNODE::STAR:
		if (CCollision::CheckCollision(this, bonusEntity)) {
			if (this->m_PlayerTag == PLAYERTAGS::BIG || this->m_PlayerTag == PLAYERTAGS::FIRE) {
				m_PreTag = m_PlayerTag;
				m_PlayerTag = PLAYERTAGS::UNDYING;
				this->loadSprite();
				this->m_UndyingTime = PLAYER_UNDYING_TIME;
			}
			if (this->m_PlayerTag == PLAYERTAGS::SMALL) {
				m_PlayerTag = PLAYERTAGS::SMALL_UNDYING;
				this->loadSprite();
				this->m_UndyingTime = PLAYER_UNDYING_TIME;
			}
		}
		break;
	case TAGNODE::FLOWER:
		if (CCollision::CheckCollision(this, bonusEntity)) {
			if (this->m_PlayerTag == PLAYERTAGS::BIG || this->m_PlayerTag == PLAYERTAGS::FIRE) {
				m_PlayerTag = PLAYERTAGS::FIRE;
				this->loadSprite();
			}
		}
		break;
	case TAGNODE::COIN:
		break;
	case TAGNODE::BRICK: case TAGNODE::GIFT_BOX:
		if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_BOTTOM)
		{
			this->m_Position.y = bonusEntity->getPosition().y - bonusEntity->getBounding().getHeight() / 2 - this->getBounding().getHeight() / 2;
			if (this->m_Velocity.y >= 0)
			{
				//this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);
				this->m_Velocity.y = VEL_PLAYER_Y_MIN;
			}
		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_TOP){
			if (this->m_State == PLAYERSTATES::JUMP) {
				this->m_Position.y = bonusEntity->getBounding().getY() + this->getBounding().getHeight() / 2;
				this->m_PlayerState->exitCurrentState(*this, new CStandState());
				this->m_PlayerState->enter(*this);
			}
			this->m_Velocity.y = VEL_DEFAULT_Y;
		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_LEFT){
			// Need to narrow the bounding of player
			if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT) {
				//	this->m_Position.x = bonusEntity->getBounding().getX() - this->getBounding().getWidth() / 2;
				this->m_Velocity.x = VEL_PLAYER_X_MIN;
			}
			else if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT){

			}
		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_RIGHT){
			// Need to narrow the bounding of player
			if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT) {
				//	this->m_Position.x = bonusEntity->getBounding().getX() + bonusEntity->getBounding().getWidth() + this->getBounding().getWidth() / 2;
				this->m_Velocity.x = VEL_PLAYER_X_MIN;
			}
			else if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT){

			}
		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_NONE){
			if (!IsCollision_Player(this, CMapManager::getInstance()->getListBonus()) &&
				m_IsFreeFall == true) {
				this->m_PlayerState->exitCurrentState(*this, new CJumpState());
				this->m_PlayerState->enter(*this);
			}
		}
		break;

	case TAGNODE::FLAG:
		if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_BOTTOM)
		{
			// Only if after collision top with flag pole tail and bottom with flag, player change into run state
			if (m_IsEnable) {
				m_IsAutoMove = true;
				if (m_Velocity.x <= 0) {
					m_Velocity.x = VEL_PLAYER_X;
				}
				this->m_PlayerState->exitCurrentState(*this, new CRunState());
				this->m_PlayerState->enter(*this);
			}
			else m_IsAutoMove = false;

		}
		break;
	case TAGNODE::FLAG_POLE:
		if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_LEFT)
		{
			if (m_State == PLAYERSTATES::JUMP || m_State == PLAYERSTATES::JUMP_SHOOT) {
				m_Position.x = bonusEntity->getPosition().x;
				this->m_PlayerState->exitCurrentState(*this, new CClimbState());
				m_IsCollision = false;

				//Just cause when player jump and collide with flag pole, need to jump a hight after that climbing
				if (m_Position.y > 60){
				}
			}

		}
		break;

	case TAGNODE::FLAG_POLE_TAIL:
		if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_LEFT)
		{
			m_IsCollision = true;

			if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_RIGHT)
			{
				m_Velocity.x = VEL_PLAYER_X_MIN;
			}
			else if (this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X) == DIRECTION::DIRECTION_LEFT) {
				m_IsCollision = false;
				this->m_Velocity.x = VEL_PLAYER_X * this->m_Direction.at(DIRECTIONINDEX::DIRECTION_X);
			}

			//m_Velocity.y = VEL_DEFAULT_Y;

		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_TOP) {
			m_IsEnable = true; // Signal for flag auto run
			if (this->m_State == PLAYERSTATES::CLIMB) {
				m_Position.y = bonusEntity->getPosition().y + this->getBounding().getHeight() / 2;
				m_Direction.at(DIRECTIONINDEX::DIRECTION_X) = DIRECTION::DIRECTION_RIGHT;

				m_Velocity.x = abs(m_Velocity.x) * m_Direction.at(DIRECTIONINDEX::DIRECTION_X);
			}
		}
		else if (CCollision::CheckCollision(this, bonusEntity) == COLDIRECTION::COLDIRECTION_NONE) {
			m_IsCollision = false;
		}
		break;

	case TAGNODE::NONE:
		if (this->m_State == PLAYERSTATES::STAND || PLAYERSTATES::RUN)
		{
			//m_IsCollision = false;
		}
		break;

	default:
		break;
	}

}

void CPlayer::handleCollisionWithEnermy(CObjectss* enermyEntity, float deltaTime) {
	//-----Handle Collision with enermy----//
	switch (enermyEntity->getTagNodeId())
	{
	case TAGNODE::MUSHROOM: case TAGNODE::TURTLE:
		if (CCollision::CheckCollision(this, enermyEntity) == COLDIRECTION::COLDIRECTION_LEFT ||
			CCollision::CheckCollision(this, enermyEntity) == COLDIRECTION::COLDIRECTION_RIGHT ||
			CCollision::CheckCollision(this, enermyEntity) == COLDIRECTION::COLDIRECTION_BOTTOM)
		{
			//if (this->m_PlayerTag == PLAYERTAGS::SMALL) {
			//	m_Velocity.y = VEL_DEFAULT_Y;
			//	this->m_PlayerState->exitCurrentState(*this, new CDieState());
			//	this->m_PlayerState->enter(*this);
			//}
			//if (this->m_PlayerTag == PLAYERTAGS::BIG || this->m_PlayerTag == PLAYERTAGS::FIRE)
			//{
			//	//undying but small and exists in 5s
			//	this->m_PlayerTag = PLAYERTAGS::SMALL_UNDYING;
			//	this->loadSprite();
			//	this->m_UndyingTime = SMALL_PLAYER_UNDYING_TIME;
			//}

			//m_IsAutoJump = false;
		}
		else if (CCollision::CheckCollision(this, enermyEntity) == COLDIRECTION::COLDIRECTION_TOP)
		{
			this->m_Position.y = enermyEntity->getPosition().y + enermyEntity->getBounding().getHeight() / 2 + this->getBounding().getHeight() / 2;

			//Dont need for auto jump
			/*this->m_PlayerState->exitCurrentState(*this, new CStandState());
			this->m_PlayerState->enter(*this);
			m_IsAutoJump = true;*/


			m_Velocity.y = VEL_PLAYER_Y_MIN;
		}

		break;
	case TAGNODE::CARNIVOROUS_PLANT:
		if (this->m_PlayerTag != PLAYERTAGS::UNDYING && this->m_PlayerTag != PLAYERTAGS::SMALL_UNDYING) {
			if (CCollision::CheckCollision(this, enermyEntity) == COLDIRECTION::COLDIRECTION_TOP) {
				this->m_PlayerState->exitCurrentState(*this, new CDieState());
				this->m_PlayerState->enter(*this);
			}
		}
		break;
	default:
		break;
	}
}

void CPlayer::drawEntity()
{
	m_listSprite.at(m_State)->Render(CCamera::setPositionEntity(vector3d(m_Position)), vector2d(m_Direction.at(DIRECTIONINDEX::DIRECTION_X), m_Direction.at(DIRECTIONINDEX::DIRECTION_Y)), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

void CPlayer::setState(PLAYERSTATES state) {
	m_State = state;
}

vector3d CPlayer::getPosition()
{
	return m_Position;
}

void CPlayer::setPosition(vector3d position) {
	m_Position = position;
}

void CPlayer::setVelocity(vector2d velocity) {
	m_Velocity = velocity;
}

CBaseState* CPlayer::getState(){
	return m_PlayerState;
}

int	CPlayer::getStateInt() {
	return m_State;
}
void CPlayer::setState(CBaseState* state) {
	m_PlayerState = state;
}

void CPlayer::setPlayerTag(int playerTag){
	this->m_PlayerTag = playerTag;
}

int CPlayer::getPlayerTag() {
	return m_PlayerTag;
}

void CPlayer::resetPlayer(vector3d newPos)
{
	m_PlayerState->exitCurrentState(*this, new CStandState(newPos));
	m_PlayerState->enter(*this);

	m_PlayerTag = PLAYERTAGS::SMALL;
	this->loadSprite();
}

int	CPlayer::getObjectType() {
	return OBJECT_TYPE::TYPE_PLAYER;
}