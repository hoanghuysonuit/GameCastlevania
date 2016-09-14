#ifndef __POPUPSCENE_H__
#define __POPUPSCENE_H__

#include "BaseScene.h"
#include "Class\Game\Utill\InformationResource.h"
#include "Class\Framework\Sprite.h"
#include "Class\Game\Scene\SceneManager.h"
#include "Class\Game\Utill\Config.h"

class CPopUpInfo
{
public:
	CPopUpInfo(){
		
		m_introInfomtion = new MapIntro();

		m_introInfomtion->m_mapName		= "1-1";
		m_introInfomtion->m_coin		= 1;
		m_introInfomtion->m_helths		= 3;
		m_introInfomtion->m_point		= m_introInfomtion->m_coin * 100;
		m_introInfomtion->m_timer		= 400;

	};
	~CPopUpInfo(){
	};

	void		setMapName(string newMapName){
		m_introInfomtion->m_mapName			= newMapName;
	};

	string		getMapName(){
		return m_introInfomtion->m_mapName;
	}

	void		setPoint(int newPoint){
		m_introInfomtion->m_point			= newPoint;
	};

	int			getPoint()
	{
		return m_introInfomtion->m_point;
	}

	void		setTimer(int newTimer){
		m_introInfomtion->m_timer			= newTimer;
	};

	int			getTimer(){
		return m_introInfomtion->m_timer;
	}

	void		setCoin(int newCoin){
		m_introInfomtion->m_coin			= newCoin;
	};

	void		addCoin(int addCoin){
		m_introInfomtion->m_coin += addCoin;
	}

	void		addPoint(int addPoint){
		m_introInfomtion->m_point += addPoint * 100;
	}

	int			getCoin(){
		return m_introInfomtion->m_coin;
	}

	void		setHelth(int newHelth){
		m_introInfomtion->m_helths			= newHelth;
	};

	int			getHelth(){
		return m_introInfomtion->m_helths;
	}

	void		addHelth(int addHelth)
	{
		if (m_introInfomtion->m_helths < 3)
			m_introInfomtion->m_helths += addHelth;
	}

	void		resetPopupInfo(){
		m_introInfomtion->m_mapName			= "1-1";
		m_introInfomtion->m_coin			= 1;
		m_introInfomtion->m_helths			= 3;
		m_introInfomtion->m_point			= m_introInfomtion->m_coin * 100;
		m_introInfomtion->m_timer			= 400;
	}

	static CPopUpInfo* getInstance(){
		if (!m_Instance)
		{
			m_Instance = new CPopUpInfo();
		}

		return	m_Instance;
	}

private:
	MapIntro*	m_introInfomtion;

private:
	static CPopUpInfo* m_Instance;
};

#endif

