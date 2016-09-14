#include "BonusManager.h"


CBonusManager::CBonusManager()
{

}


CBonusManager::~CBonusManager()
{
}


void CBonusManager::pushEnvent(int event_item)
{
	m_EventList.push_back(event_item);
}

void CBonusManager::popEnvent(int event_item)
{
	m_EventList.pop_back();
}

void CBonusManager::handleEnvent(float deltaTime) {

}
