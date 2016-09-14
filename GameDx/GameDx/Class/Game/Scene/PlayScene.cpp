#include "PlayScene.h"
#include "Class\Mathematics\Collision.h"
#include "Class\Game\Scene\PopupInfo.h"
#include "Class\Game\Entity\Map\MapManager.h"
#include "Class\Game\Algorithsm\QuadTree.h"
#include "Class\Game\Entity\Player\Player.h"
#include "Class\Game\Scene\GameOverScene.h"


inline int getIndexRemove(vector<CObjectss*> list) {
	for (int i = 0; i < list.size(); ++i) {
		if (list.at(i)->isDestroy) {
			return i;
		}
	}

	//std::vector<CObjectss*>::iterator it;
	//it = std::find(list.begin(), list.end(), entity);
}


CPlayScene::CPlayScene()
{
	this->initScene();
}

CPlayScene::~CPlayScene()
{
}

bool CPlayScene::initScene()
{
	m_backgroud = new CSprite(CInfomationResource::backgroundPlayScene);
	m_listObjectInViewport = new vector<CObjectss*>();

	CMapManager::getInstance();

	m_treeGame = new CQuadTree();

	m_treeGame->CreateTree();

//	m_Sound = CAudio::getInstance()->LoadSound(L"Resource//Sound//Pokemon_Pokemon_-_No.wav");
	m_actionDieTimer = 0;
	CPlayer::getInstance();

	return true;
}

void CPlayScene::updateScene(double deltaTime)
{
	//CAudio::getInstance()->PlaySoundW(m_Sound);
	CPlayer::getInstance()->updateEntity(deltaTime);

	CCamera::getInstance()->Update(CPlayer::getInstance()->getPosition());

	m_listObjectInViewport->clear();
	m_treeGame->Retrieve(CCamera::getInstance()->getBoundingScreen(), m_listObjectInViewport);

	CPlayer::getInstance()->handleCollisionWithTile(deltaTime);

	if (CMapManager::getInstance()->getListBonusItem().size() != 0)
	{
		for (int i = 0; i < CMapManager::getInstance()->getListBonusItem().size(); i++)
		{
			CPlayer::getInstance()->handleCollisionWithBonus(CMapManager::getInstance()->getListBonusItem().at(i), deltaTime);
			CMapManager::getInstance()->getListBonusItem().at(i)->updateEntity(deltaTime);
		}
	}

	for (int i = 0; i < m_listObjectInViewport->size(); ++i) {
		if (m_listObjectInViewport->at(i)->isDestroy) {
			m_listObjectInViewport->erase(m_listObjectInViewport->begin() + getIndexRemove(*m_listObjectInViewport));
		}

		if (m_listObjectInViewport->at(i)->getObjectType() == OBJECT_TYPE::TYPE_BONUS) {
			CPlayer::getInstance()->handleCollisionWithBonus(m_listObjectInViewport->at(i), deltaTime);
		}
		else if (m_listObjectInViewport->at(i)->getObjectType() == OBJECT_TYPE::TYPE_ENERMY) {
			CPlayer::getInstance()->handleCollisionWithEnermy(m_listObjectInViewport->at(i), deltaTime);
		}

		m_listObjectInViewport->at(i)->updateEntity(deltaTime);
	}

	this->checkChangeScene(deltaTime);
}

void CPlayScene::updateScene(CKeyBoard* keyboard)
{
	if (keyboard->KeyPress(DIK_P))
		return;
	CPlayer::getInstance()->updateEntity(keyboard);
}

void CPlayScene::renderScene()
{
	m_backgroud->Render(CCamera::getInstance()->setPositionEntity(vector3d(CCamera::getInstance()->getPosisionCamera())), vector2d(1.0f, 1.0f), 0, DRAWCENTER_LEFT_TOP);
	
	wchar_t temp[100];
	_itow(CPopUpInfo::getInstance()->getPoint(), temp, 10);
	CText::getInstace()->Draw(temp, vector3d(50, 24, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);
		
	ZeroMemory(temp, 100);
	_itow(CPopUpInfo::getInstance()->getCoin(), temp, 10);
	CText::getInstace()->Draw(temp, vector3d(110, 24, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);

	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, CPopUpInfo::getInstance()->getMapName().c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, CPopUpInfo::getInstance()->getMapName().c_str(), -1, wstr, wchars_num);

	CText::getInstace()->Draw(wstr, vector3d(160, 24, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);

	ZeroMemory(temp, 100);
	_itow(CPopUpInfo::getInstance()->getTimer(), temp, 10);
	CText::getInstace()->Draw(temp, vector3d(220, 24, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);

	/*HELTH VIEWER*/
	ZeroMemory(temp, 100);
	_itow(CPopUpInfo::getInstance()->getHelth(), temp, 10);
	CText::getInstace()->Draw(temp, vector3d(42, 57, 0), DEFAULT_FONT_COLOR, 8, DT_CENTER, DEFAULT_FONTNAME);
	/*********************************************************************************************************/

	if (m_listObjectInViewport->size())
	for (int i = 0; i < m_listObjectInViewport->size(); ++i)
		m_listObjectInViewport->at(i)->drawEntity();

	if (CMapManager::getInstance()->getListBonusItem().size() != 0)
	{
		for (int i = 0; i < CMapManager::getInstance()->getListBonusItem().size(); i++)
		{
			CMapManager::getInstance()->getListBonusItem().at(i)->drawEntity();
		}
	}

	if (m_listObjectInViewport->size())
	for (int i = 0; i < m_listObjectInViewport->size(); ++i)

		m_listObjectInViewport->at(i)->drawEntity();

	CPlayer::getInstance()->drawEntity();
}

void	CPlayScene::checkChangeScene(float deltaTime)
{
	if (CPlayer::getInstance()->getPosition().x >= 3230 && CMapManager::getInstance()->getCurrentMapINT() == 1)
	{
		CPopUpInfo::getInstance()->setMapName("1-2");
		CPopUpInfo::getInstance()->setTimer(1000);
		CPlayer::getInstance()->resetPlayer(vector3d(70, 50, 0.5));

		CMapManager::getInstance()->resetToMap(1);
		CCamera::getInstance()->setPositionCamera(vector3d(0, 240, 0));

		CBaseScene* tempScene = CSceneManager::getInstance()->getScene().top();
		CSceneManager::getInstance()->getScene().pop();
		delete[] tempScene;

		CSceneManager::getInstance()->getScene().push(new CIntroMap());
	}
	else if (CPlayer::getInstance()->getPosition().x >= 3820 && CMapManager::getInstance()->getCurrentMapINT() == 2){
		

		CBaseScene* tempScene = CSceneManager::getInstance()->getScene().top();
		CSceneManager::getInstance()->getScene().pop();
		delete[] tempScene;

		CSceneManager::getInstance()->getScene().push(new CGameOver());
	}


	if (CPlayer::getInstance()->getStateInt() == PLAYERSTATES::DIE)
	{
		if (m_actionDieTimer < 1000)
		{
			m_actionDieTimer += deltaTime;
			return;
		}

		CPopUpInfo::getInstance()->setHelth(CPopUpInfo::getInstance()->getHelth() - 1);

		CBaseScene* tempScene = CSceneManager::getInstance()->getScene().top();
		CSceneManager::getInstance()->getScene().pop();
		delete[] tempScene;

		if (CPopUpInfo::getInstance()->getHelth() > 0)
			CSceneManager::getInstance()->getScene().push(new CIntroMap());
		else
			CSceneManager::getInstance()->getScene().push(new CGameOver());

		CPlayer::getInstance()->resetPlayer(vector3d(70, 50, 0.5));
		CCamera::getInstance()->setPositionCamera(vector3d(0, 240, 0));

		m_actionDieTimer = 0;

	}
}