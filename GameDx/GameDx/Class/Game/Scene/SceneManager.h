#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Class\Game\Utill\stdafx.h"
#include <stack>
#include "Class\Game\Utill\Config.h"
#include "Class\Game\Scene\BaseScene.h"
#include "Class\Game\Scene\MenuScene.h"
#include "Class\Game\Scene\PlayScene.h"
#include "Class\Game\Scene\IntroMap.h"
#include "Class\Game\Scene\SelectedScene.h"

class CSceneManager
{
public:

	static	CSceneManager*				getInstance();
			std::stack<CBaseScene*>&	getScene();
	static	void						initDevice(LPDIRECT3DDEVICE9 device);
			void						init();

private:
	CSceneManager();
	~CSceneManager();

	static	CSceneManager*				m_Instance;

private:
	static	LPDIRECT3DDEVICE9			m_Device;
			std::stack<CBaseScene*>		m_ListScene;
};

#endif