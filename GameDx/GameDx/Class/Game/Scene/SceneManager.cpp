#include "SceneManager.h"


CSceneManager*			CSceneManager::m_Instance	= NULL;
LPDIRECT3DDEVICE9		CSceneManager::m_Device		= 0;

CSceneManager::CSceneManager()
{
	this->init();
}

CSceneManager::~CSceneManager()
{
}

CSceneManager* CSceneManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new CSceneManager();
	return m_Instance;
}

void CSceneManager::initDevice(LPDIRECT3DDEVICE9 device)
{
	m_Device		= device;
}

void CSceneManager::init()
{
	m_ListScene.push(new CMenuScene());
}

std::stack<CBaseScene*>& CSceneManager::getScene()
{
	return m_ListScene;
}
