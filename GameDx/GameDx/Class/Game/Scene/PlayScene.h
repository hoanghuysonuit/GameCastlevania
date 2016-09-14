#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "BaseScene.h"
#include "Class\Game\Algorithsm\QuadTree.h"
#include "Class\Framework\CAudio.h"


class CPlayScene :
	public CBaseScene
{
public:
	CPlayScene();
	~CPlayScene();

	virtual bool initScene()						override;
	virtual void updateScene(double deltaTime)		override;
	virtual void updateScene(CKeyBoard* keyboard)	override;
	virtual void renderScene()						override;

			void checkChangeScene(float deltaTime);

private:
	CQuadTree*				m_treeGame;
	vector<CObjectss*>*		m_listObjectInViewport;
	CSound*					m_Sound;
	CSprite*				m_backgroud;
	float					m_actionDieTimer;
};

#endif
