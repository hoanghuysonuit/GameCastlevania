#include "SelectedScene.h"
#include <ctime>
#include <stack>
#include "Class\Game\Scene\PopupInfo.h"



CSelectedScene::CSelectedScene()
{
	this->initScene();
}


CSelectedScene::~CSelectedScene()
{
	CSprite* tempSprite;
	while (!m_listBackgroud.empty())
	{
		tempSprite		= m_listBackgroud.back();
		m_listBackgroud.pop_back();
		delete tempSprite;
		tempSprite		= NULL;
	}

	SAFE_RELEASE(m_selectArrow);
}

bool CSelectedScene::initScene()
{
	m_selectedMap		= MAP_NUM::MAP_1;
	m_enterIntroScene	= false;

	m_listBackgroud.push_back(new CSprite(CInfomationResource::map1SelectedIcon));
	m_listBackgroud.push_back(new CSprite(CInfomationResource::map2SelectedIcon));
	m_listBackgroud.push_back(new CSprite(CInfomationResource::selectedMapBackground));

	m_selectArrow		= new CSprite(CInfomationResource::arrowSelected, 1, 2);
	return true;
}

void CSelectedScene::updateScene(double deltaTime)
{
	if (m_enterIntroScene)
	{
		if (m_selectedMap == 1)
			CPopUpInfo::getInstance()->setMapName("1-1");
		else if (m_selectedMap == 2)
			CPopUpInfo::getInstance()->setMapName("1-2");

		CBaseScene* tempScene = CSceneManager::getInstance()->getScene().top();
		CSceneManager::getInstance()->getScene().pop();
		delete[] tempScene;

		CSceneManager::getInstance()->getScene().push(new CIntroMap());
	}
}

void CSelectedScene::updateScene(CKeyBoard* keybard)
{
	if (keybard->KeyPress(DIK_UP) || keybard->KeyPress(DIK_DOWN))
		m_selectedMap += 1;
	if (m_selectedMap > 2)
		m_selectedMap = 1;

	if (keybard->KeyPress(DIK_RETURN))
		m_enterIntroScene = true;
}

void CSelectedScene::renderScene()
{
	m_listBackgroud.at(2)->Render(vector3d(0, 0, 0.5f), vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP);
	m_listBackgroud.at(0)->Render(vector3d(40, 45, 0.5f),	vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP);
	m_listBackgroud.at(1)->Render(vector3d(40, 100, 0.5f),	vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP);

	if (m_selectedMap == 1)
		m_selectArrow->Render(vector3d(40, 45, 0.5f), vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP, true, 3);
	else if (m_selectedMap == 2)
		m_selectArrow->Render(vector3d(40, 100, 0.5f), vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP, true, 3);

	wchar_t temp[100];
	ZeroMemory(temp, 100);
	string x = "Select map";
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, x.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, x.c_str(), -1, wstr, wchars_num);
	CText::getInstace()->Draw(wstr, vector3d(125, 210, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);	
}