#include "GameOverScene.h"
#include <ctime>
#include <stack>
#include "Class\Game\Scene\PopupInfo.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Entity\Map\MapManager.h"



CGameOver::CGameOver()
{
	this->initScene();
	m_actionChangeSceneTimer = 0;
}


CGameOver::~CGameOver()
{
}

bool CGameOver::initScene()
{
	return true;
}

void CGameOver::updateScene(double deltaTime)
{
	if (m_actionChangeSceneTimer < 3000)
	{
		m_actionChangeSceneTimer += deltaTime;
		return;
	}
	m_actionChangeSceneTimer = 0;

	CPopUpInfo::getInstance()->setMapName("1-2");
	CPopUpInfo::getInstance()->setTimer(1000);
	CPlayer::getInstance()->resetPlayer(vector3d(70, 50, 0.5));

	CMapManager::getInstance()->resetToMap(0);
	CCamera::getInstance()->setPositionCamera(vector3d(0, 240, 0));

	CBaseScene* tempScene = CSceneManager::getInstance()->getScene().top();
	CSceneManager::getInstance()->getScene().pop();
	delete[] tempScene;

	CSceneManager::getInstance()->getScene().push(new CMenuScene());
}

void CGameOver::updateScene(CKeyBoard* keybard)
{

}

void CGameOver::renderScene()
{
	string x;
	if (m_Win)
		x = "CONGRATULATION...YOU WIN";
	else
		x = "GAME OVER";
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, x.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, x.c_str(), -1, wstr, wchars_num);
	CText::getInstace()->Draw(wstr, vector3d(120, 125, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);

	delete[] wstr;
}