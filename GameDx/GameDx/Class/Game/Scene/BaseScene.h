#ifndef __CBASESCENE_H__
#define __CBASESCENE_H__

#include "Class\Game\Utill\stdafx.h"
#include "Class\Framework\KeyBoard.h"

class CBaseScene
{
public:
	CBaseScene(){};
	virtual	~CBaseScene(){};

	virtual bool initScene() = 0;
	virtual void updateScene(double deltaTime) = 0;
	virtual void updateScene(CKeyBoard*) = 0;
	virtual void renderScene() = 0;

private:
	/*char*			m_Tag;*/
};

#endif
