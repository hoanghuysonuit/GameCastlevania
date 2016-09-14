#ifndef __BULLETMANAGER_H__
#define __BULLETMANAGER_H__

#include "Class\Game\Algorithsm\Singleton.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\StaticEntity.h"
#include "Class\Game\Entity\Bullet\BulletNormal.h"
#include "Class\Game\Algorithsm\CObjectPool.h"

class CBulletManager : public CObjectPool<CBulletManager>
{
public:
	CBulletManager();
	~CBulletManager();

	void			updateBullet(float			deltaTime);
	void			updateBullet(CStaticEntity*	staticEntity);
	void			updateBullet(CMovable*		player);

	void			getBullet	(int			styleBullet);
	void			createBullet(int			styleBullet);


private:
	vector<CBulletNormal*>						m_listBullet;

};

#endif