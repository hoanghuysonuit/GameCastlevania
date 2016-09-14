#include "Class\Game\Test\Test.h"
#include "Class\Framework\Camera.h"
#include "Class\Framework\Timer.h"
#include "Class\Mathematics\AABB.h"


Test::Test(LPDIRECT3DDEVICE9 device)
{

	m_SpriteTest = new CSprite(L"Resource//Image//Game//Sprites//Others//rock.png");
	m_position = D3DXVECTOR3(100.0f, 300.0f, 0.0f);

	m_StaticSprite = new CSprite(L"Resource//Image//Game//Sprites//Others//popup.png");
	m_positionStatic = D3DXVECTOR3(200.0f, 400.0f, 0.0f);


	//m_SpriteTest	= new CSprite(L"Resource//Test//BOX_OPENED.png", 1, 3, 3, 0);
	//m_StaticSprite	= new CSprite(L"Resource//Test//BOX_CLOSED.png", 1, 1, 1, 0);
	//m_position	= D3DXVECTOR3(10.0, 20.0, 0.0f);


	RECT rect		= {	
						this->m_position.x,
						this->m_position.y,
						this->m_position.x + (m_SpriteTest->getScrRect().right - m_SpriteTest->getScrRect().left),
						this->m_position.y + (m_SpriteTest->getScrRect().top - m_SpriteTest->getScrRect().bottom)
					  };

	RECT rect1 = {
		m_positionStatic.x,
		m_positionStatic.y,
		m_positionStatic.x + (m_StaticSprite->getScrRect().right - m_StaticSprite->getScrRect().left),
		m_positionStatic.y + (m_StaticSprite->getScrRect().top - m_StaticSprite->getScrRect().bottom)
	};
	vx = new vector2d(1.0f, 1.0f);
	moveBox = new CBox2D();
	dynamicBox = new CBox2D();
	m_Bounding = new CBox2D(device, rect, vector2dZero);
	//moveBox = m_Bounding;
	m_Text			= new CText();

	//m_StaticObject->m_Bounding = new CBox2D(m_StaticObject->getBounding());
	backgroundMussic = CAudio::getInstance()->LoadSound(L"sound1.wav");


	m_Bounding1 = new CBox2D(device, rect1, vector2dZero);
	//dynamicBox = m_Bounding;

	/*moveBox = new CBox2D();
	dynamicBox = new CBox2D();*/
	moveBox->setVelocityX(vx->x);
	moveBox->setVelocityY(vx->y);
	moveBox->setHeight(abs(m_SpriteTest->getScrRect().top - m_SpriteTest->getScrRect().bottom));
	moveBox->setWidth(abs(m_SpriteTest->getScrRect().right - m_SpriteTest->getScrRect().left));
	moveBox->setX(this->m_position.x);
	moveBox->setY(this->m_position.y);

	dynamicBox->setVelocityX(0.0f);
	dynamicBox->setVelocityY(0.0f);
	dynamicBox->setHeight(abs(m_StaticSprite->getScrRect().top - m_StaticSprite->getScrRect().bottom));
	dynamicBox->setWidth(abs(m_StaticSprite->getScrRect().right - m_StaticSprite->getScrRect().left));
	dynamicBox->setX(m_positionStatic.x);
	dynamicBox->setY(m_positionStatic.y);


	//m_StaticObject->m_Bounding = new CBox2D(m_StaticObject->getBounding(), vector2dZero);
}

Test::~Test()
{
	SAFE_RELEASE(m_SpriteTest);
	SAFE_RELEASE(m_Text);
	SAFE_RELEASE(m_Bounding);

	SAFE_RELEASE(m_StaticObject);
}

void Test::Update(CKeyBoard* device)
{
	

	if (device->KeyDown(DIK_RIGHT))
		this->m_position.x += vx->x;

	if (device->KeyDown(DIK_LEFT))
	{
		vx->x = vx->x * (-1);
		this->m_position.x += vx->x;
	}

	if (device->KeyDown(DIK_UP))
	{

		CAudio::getInstance()->StopSound(backgroundMussic);
		this->m_position.y += vx->y;
	}


	if (device->KeyDown(DIK_DOWN))
	{
	CAudio::getInstance()->LoopSound(backgroundMussic);
		vx->y = vx->y *(-1);
		this->m_position.y += vx->y;
	}

	if (m_position.x <= 0) m_position.x = 0;

	if (m_position.y <= 20) m_position.y = 20;

	this->moveBox->setVelocityX(vx->x);
	this->moveBox->setVelocityY(vx->y);
	this->moveBox->setX(this->m_position.x);
	this->moveBox->setY(this->m_position.y);

	m_Bounding->update(CTimer::getInstance()->getElapedTime(), vector2d(m_position.x, m_position.y));


	vx->x = abs(vx->x);
	vx->y = abs(vx->y);
}

void Test::Render()
{
	
	m_SpriteTest->Render(CCamera::setPositionEntity(m_position), vector2d(1.0f, 1.0f), 0.0f, DRAWCENTER_LEFT_TOP);
	//m_SpriteTest->Render(CCamera::setPositionEntity(vector3d(m_Bounding->getX(),m_Bounding->getY(), 0)), vector2d(1.0f, 1.0f), 0.0f, DRAWCENTER_LEFT_TOP);
	m_StaticSprite->Render(CCamera::setPositionEntity(m_positionStatic), vector2d(1.0f, 1.0f), 0.0f, DRAWCENTER_LEFT_TOP);
	//m_StaticSprite->Render(CCamera::setPositionEntity(vector3d(m_Bounding1->getX(),m_Bounding1->getY(),0)), vector2d(1.0f, 1.0f), 0.0f, DRAWCENTER_LEFT_TOP);
	/*OutputDebugString(L"Pos x: ");
	OutputDebugString(_itow(m_position.x, new WCHAR[1], 10));
	OutputDebugString(L"\n");
	OutputDebugString(L"Pos y: ");
	OutputDebugString(_itow(m_position.y, new WCHAR[1], 10));
	OutputDebugString(L"\n");*/
}

D3DXVECTOR3 Test::getPosision()
{
	return m_position;
}
