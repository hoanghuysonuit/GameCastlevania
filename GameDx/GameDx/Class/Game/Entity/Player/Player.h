#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Framework\Camera.h"
#include "Class\Game\State\BaseState.h"
#include "Class\Game\Algorithsm\Singleton.h"
#include "Class\Game\Utill\ShowBouding.h"
#include "Class\Game\Utill\ResourceManager\BaseResource.h"
#include "Class\Game\Utill\ResourceManager\PlayerResource.h"

//#include <vld.h>

class CBaseState;

#ifndef __CPLAYER_H__
#define __CPLAYER_H__

class CBaseState;

class CPlayer : public CMovable, public CSingleton<CPlayer>
{
public:
	CPlayer();
	CPlayer(directDevice);
	~CPlayer();

	virtual bool			initEntity()											override;
	virtual void			updateEntity(float deltaTime)							override;
	virtual void			updateEntity(RECT* camera)								override;
	virtual void			updateEntity(CKeyBoard *device)							override;
	virtual void			drawEntity()											override;
	virtual	vector3d		getPosition()											override;
	virtual bool			loadSprite()											override;
	virtual int				getTagNodeId()											override;
	virtual int				getObjectType()											override;

	void					handleCollisionWithBonus(CObjectss* bonusEntity, float deltaTime);
	void					handleCollisionWithEnermy(CObjectss* enermyEntity, float deltaTime);
	void					handleCollisionWithTile(float deltaTime);
public:
	void					setPosition(vector3d position);
	void					setState(PLAYERSTATES state);
	void					setVelocity(vector2d velocity);
	void					setState(CBaseState* state);
	CBaseState*				getState();
	int						getStateInt();
	void					setPlayerTag(int playerTag);
	int						getPlayerTag();
	void					resetPlayer(vector3d);

	bool					m_IsCollision; // Use for collision with Flag Pole Tail
	bool					m_IsAutoMove; // Signal for Flag auto run
	bool					m_IsAutoJump; // In case collision top wirh enermies
	bool					m_IsFreeFall;
	vector<int>				m_Direction;
	vector3d				m_PreJumpPos;
protected:
	vector2d				m_Acceleration;
	int						m_PlayerTag;
	CBaseState*				m_PlayerState;
	int						m_UndyingTime;

	int						m_PreTag;
private:
};
#endif
