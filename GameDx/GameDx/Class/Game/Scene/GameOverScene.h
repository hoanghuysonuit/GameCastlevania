#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__

#include "BaseScene.h"
#include "Class\Framework\Sprite.h"
#include "Class\Framework\Text.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Scene\SceneManager.h"
#include "Class\Game\Scene\PlayScene.h"
class CGameOver :
	public CBaseScene
{
public:
	CGameOver();
	~CGameOver();

	virtual bool initScene()						override;
	virtual void updateScene(double deltaTime)		override;
	virtual void updateScene(CKeyBoard*)			override;
	virtual void renderScene()						override;

private:
	float		m_actionChangeSceneTimer;
	bool		m_Win;
};

#endif