#ifndef __C_BONUS_MANAGER_H__
#define __C_BONUS_MANAGER_H__

#include "Brick.h"
#include "Coin.h"
#include "Star.h"


class CBonusManager
{
public:
	CBonusManager();
	~CBonusManager();
	
	void pushEnvent(int event_item);
	void popEnvent(int event_item);
	void handleEnvent(float deltaTime);

private:
	vector<int> m_EventList;
};

#endif
