#include "Elevator.h"
#include "Class\Game\Utill\ResourceManager\TileResource.h"

Elevator::Elevator()
{
	this->initEntity();
}

Elevator::~Elevator()
{
	SAFE_RELEASE(m_ResouceImage);

	if (!m_listSprite.empty()) {
		for (int i = 0; i < m_listSprite.size(); ++i) {
			SAFE_RELEASE(m_listSprite.at(i));
			m_listSprite.at(i) = nullptr;
		}
	}
}

Elevator::Elevator(vector2d pos, ELEVATOR_STATE ElevatorState)
{
	this->m_Position.x	= pos.x;
	this->m_Position.y	= pos.y;

	this->m_Type		= ElevatorState;

	this->initEntity();
	
	this->ELEVATOR_POSITION_Y_MAX = pos.y + 2*this->m_listSprite.at(0)->getFrameInfo().Width;
	this->ELEVATOR_POSITION_Y_MIN = pos.y - this->m_listSprite.at(0)->getFrameInfo().Width;

}

bool Elevator::initEntity()
{

	this->m_TagNode			= "Elevator";
	this->m_State			= 0;					// dont need state;
	this->m_Velocity		= vector2d(ELEVATOR_VELOCITY_X, ELEVATOR_VELOCITY_Y);

	this->m_ResouceImage	= new CTileResource();
	this->loadSprite();

	this->m_Bounding		= new CBox2D(0, 0, 0, 0);
	this->getBounding();
	
	return true;
}

bool Elevator::loadSprite()
{
	this->m_listSprite.push_back(new CSprite(this->m_ResouceImage->getImage(TYPEOFTILE::TOF_ELEVATOR), 1, 1, 1, 0));
	return true;
}

void Elevator::updateEntity(float deltaTime)
{
	switch (m_Type)
	{
	case ELEVATOR_STATE::DOWN:
		if (SIGN(this->m_Velocity.y) == DIRECTION::DIRECTION_UP)
			this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);

		this->m_Position.y += this->m_Velocity.y *deltaTime / 100;
		//this->setPosition(vector3d(this->getPosition().x, this->getPosition().y - abs(this->getVelocity().y * deltaTime / 100), 0));
		break;
	case ELEVATOR_STATE::UP:
		if (SIGN(this->m_Velocity.y) == DIRECTION::DIRECTION_DOWN)
			this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);

		this->m_Position.y += this->m_Velocity.y *deltaTime / 100;
		//this->setPosition(vector3d(this->getPosition().x, this->getPosition().y + abs(this->getVelocity().y * deltaTime / 100), 0));
		break;
	case ELEVATOR_STATE::UP_DOWN:
		if (this->m_Position.y <= ELEVATOR_POSITION_Y_MIN)
		{
			if (SIGN(this->m_Velocity.y) == DIRECTION::DIRECTION_DOWN)
				this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);
		}
		else if (this->m_Position.y >= ELEVATOR_POSITION_Y_MAX){
			if (SIGN(this->m_Velocity.y) == DIRECTION::DIRECTION_UP)
				this->m_Velocity.y = CHANGE_DIRECTION(this->m_Velocity.y);
		}
		this->m_Position.y += this->m_Velocity.y * deltaTime / 100;
		break;
	case ELEVATOR_STATE::RIGHT_LEFT:
		if (this->m_Position.x <= ELEVATOR_POSITION_X_MIN)
		{
			if (SIGN(this->m_Velocity.x) == DIRECTION::DIRECTION_LEFT)
				this->m_Velocity.x = CHANGE_DIRECTION(this->m_Velocity.x);
		}
		else if (this->m_Position.x >= ELEVATOR_POSITION_X_MAX){
			if (SIGN(this->m_Velocity.y) == DIRECTION::DIRECTION_RIGHT)
				this->m_Velocity.x = CHANGE_DIRECTION(this->m_Velocity.x);
		}
		this->m_Position.x += this->m_Velocity.x * deltaTime / 100;
		break;
	default:
		break;
	}
}

void Elevator::updateEntity(RECT* camera) {

}

void Elevator::updateEntity(CKeyBoard* input)
{
}

void Elevator::drawEntity()
{
	m_listSprite.at(0)->Render(CCamera::setPositionEntity(m_Position), vector2d(SIGN(m_Velocity.x) * (-1), abs(m_Velocity.y / m_Velocity.y) * 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}

int	Elevator::getTagNodeId()
{
	return TAGNODE::ELEVATOR;
}

int Elevator::getObjectType() {
	return OBJECT_TYPE::TYPE_TILE;
}