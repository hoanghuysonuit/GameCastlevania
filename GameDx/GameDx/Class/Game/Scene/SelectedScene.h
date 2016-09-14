#ifndef __SELECTED_SCENE_H__
#define __SELECTED_SCENE_H__

#include "BaseScene.h"
#include "Class\Framework\Sprite.h"
#include "Class\Framework\Text.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Scene\SceneManager.h"
#include "Class\Game\Scene\PlayScene.h"

class CSelectedScene :
	public CBaseScene
{
public:
	CSelectedScene();
	~CSelectedScene();

	virtual bool initScene()						override;
	virtual void updateScene(double deltaTime)		override;
	virtual void updateScene(CKeyBoard*)			override;
	virtual void renderScene()						override;

private:
	vector<CSprite*>	m_listBackgroud;
	CSprite*			m_selectArrow;
	float				m_selectedMap;
	bool				m_enterIntroScene;
};

#endif