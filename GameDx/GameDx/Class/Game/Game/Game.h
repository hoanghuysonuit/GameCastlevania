/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/


#ifndef __CGAME_H__
#define __CGAME_H__


#include "Class\Framework\Windows.h"
#include "Class\Framework\Camera.h"
#include "Class\Game\Test\Test.h"
#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Scene\SceneManager.h"


class CGame
{
public:
	CGame(HINSTANCE hInstance);
	~CGame(void);

	void initGame();
	void updateGame(double deltaTime);
	void renderGame();

private:
	CWindows*				m_Windows;
	CKeyBoard*				m_Keyboard;
	Test*					m_Test;
};

#endif
