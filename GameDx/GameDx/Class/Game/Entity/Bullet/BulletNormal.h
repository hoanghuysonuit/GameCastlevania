#ifndef __BULLET_H__
#define __BULLET_H__

#include "Class\Game\Entity\MovableEntity.h"

class CBulletNormal	: public CMovable
{
public:
	CBulletNormal();
	~CBulletNormal();

	virtual		bool					initEntity()										override;
	virtual		void					updateEntity(CKeyBoard* device)						override;
	virtual		void					updateEntity(float deltaTime)						override;
	virtual		void					updateEntity(RECT* camera)							override;
	virtual		void					drawEntity()										override;
	virtual		bool					loadSprite()										override;
	virtual		vector3d				getPosition();

				void					setState(int newState);
				int						getState();

				int temp;

private:

};

#endif
