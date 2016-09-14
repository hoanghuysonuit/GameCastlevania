#ifndef __INTROSTAGESCENE_H__
#define __INTROSTAGESCENE_H__

#include "BaseScene.h"
#include "Class\Framework\Sprite.h"
#include "Class\Framework\Text.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Scene\SceneManager.h"
#include "Class\Game\Scene\PlayScene.h"
class CIntroMap :
	public CBaseScene
{
public:
	CIntroMap();
	~CIntroMap();

	virtual bool initScene()						override;
	virtual void updateScene(double deltaTime)		override;
	virtual void updateScene(CKeyBoard*)			override;
	virtual void renderScene()						override;

	void	setMapLevel();

private:
	CSprite*	m_backgroud;
	CSprite*	m_marioIcon;
	float		m_timeWaiting;

	static		MapIntro	m_mapIntro;
};

#endif