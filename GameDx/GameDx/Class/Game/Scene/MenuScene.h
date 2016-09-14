#ifndef __CMENUSCENE_H__
#define __CMENUSCENE_H__

#include "Class\Framework\Sprite.h"
#include "Class\Framework\Text.h"
#include "Class\Game\Scene\BaseScene.h"
#include "Class\Framework\Windows.h"

class CMenuScene :
	public CBaseScene
{
public:
	CMenuScene();
	~CMenuScene();

	virtual bool initScene()						override;
	virtual void updateScene(CKeyBoard*)			override;
	virtual void updateScene(double deltaTime)		override;
	virtual void renderScene()						override;

private:
	CSprite*		m_Background;
	CSprite*		m_selectArrow;
	bool			m_enterTheGame;
};
#endif
