#ifndef __TEST_H__
#define __TEST_H__

#include "Class\Game\Utill\stdafx.h"
#include "Class\Framework\Sprite.h"
#include "Class\Framework\KeyBoard.h"
#include "Class\Framework\Text.h"
#include "Class\Framework\CAudio.h"
#include "Class\Mathematics\Box2D.h"
#include "Class\Game\Entity\MovableEntity.h"
#include "Class\Game\Entity\StaticEntity.h"

class Test
{
public:
	Test(LPDIRECT3DDEVICE9);
	~Test();
	D3DXVECTOR3	getPosision();

	void	Update(CKeyBoard* device);
	void	Render();

private:
	CSprite*	m_SpriteTest;
	D3DXVECTOR3	m_position;
	CText*		m_Text;
	CBox2D*		m_Bounding;
	CBox2D*		m_Bounding1;
	CMovable*	MovableObject;

	CSprite*		m_StaticSprite;

	CStaticEntity*	m_StaticObject;
	D3DXVECTOR3		m_positionStatic;

	CAudio* testSound;
	CSound* backgroundMussic;

	vector2d *vx;
	CBox2D *moveBox;
	CBox2D *dynamicBox;

};

#endif
