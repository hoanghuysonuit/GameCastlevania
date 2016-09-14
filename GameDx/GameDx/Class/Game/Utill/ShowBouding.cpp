#include "ShowBouding.h"

CShowBouding* CShowBouding::m_instance = NULL;

CShowBouding::CShowBouding()
{
	this->initEntity();
}


CShowBouding::~CShowBouding()
{

}

CShowBouding* CShowBouding::getInstance(){
	if (!m_instance){
		m_instance = new CShowBouding();
	}
	return m_instance;
}

bool CShowBouding::initEntity(){
	this->m_listSprite.push_back(new CSprite(CInfomationResource::boundingsprite, 1, 1));
	return true;
}

void CShowBouding::drawBouding(CBaseEntity* entity){
	this->m_listSprite.at(0)->Render(CCamera::getInstance()->setPositionEntity(vector3d(entity->getBounding().getX() , entity->getBounding().getY(), 0)), 
																							vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	this->m_listSprite.at(0)->Render(CCamera::getInstance()->setPositionEntity(vector3d(entity->getBounding().getX() + entity->getBounding().getWidth(), entity->getBounding().getY(), 0)), 
																							vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	this->m_listSprite.at(0)->Render(CCamera::getInstance()->setPositionEntity(vector3d(entity->getBounding().getX(), entity->getBounding().getY() - entity->getBounding().getHeight(), 0)), 
																							vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
	this->m_listSprite.at(0)->Render(CCamera::getInstance()->setPositionEntity(vector3d(entity->getBounding().getX() + entity->getBounding().getWidth(), entity->getBounding().getY() - entity->getBounding().getHeight(), 0)), 
																							vector2d(1, 1), 0, DRAWCENTER_MIDDLE_MIDDLE, true, 10);
}
