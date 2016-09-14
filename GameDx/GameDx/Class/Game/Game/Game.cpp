#include "Class\Game\Game\Game.h"
#include "Class\Framework\Sprite.h"


CGame::CGame(HINSTANCE hInstance)
{
	m_Windows	= new CWindows(hInstance);
	m_Windows->initWindowGame();

	CSprite::initSpriteHandler(m_Windows->getSpriteHandler());
	CText::InitDevice(m_Windows->getDevice(), m_Windows->getSpriteHandler());
	
	m_Keyboard	= new CKeyBoard(hInstance, m_Windows->getWindowHandler());
	CAudio::getInstance()->Init_DirectSound(m_Windows->getWindowHandler());

	CSceneManager::initDevice(m_Windows->getDevice());

	this->initGame();
}

CGame::~CGame()
{
	SAFE_RELEASE(m_Windows);
	SAFE_RELEASE(m_Keyboard);
}


void CGame::initGame()
{
	CSceneManager::getInstance()->init();
}
void CGame::updateGame(double deltaTime)
{
	m_Keyboard->Update();


	if (m_Keyboard->KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);

	CSceneManager::getInstance()->getScene().top()->updateScene(m_Keyboard);
	CSceneManager::getInstance()->getScene().top()->updateScene(deltaTime);

}
void CGame::renderGame()
{
	if (this->m_Windows->startDraw()) {
		CSceneManager::getInstance()->getScene().top()->renderScene();
	}
	this->m_Windows->stopDraw();
}