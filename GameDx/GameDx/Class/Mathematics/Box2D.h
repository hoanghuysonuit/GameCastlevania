#ifndef __CBOX2D_H__
#define __CBOX2D_H__

#include "Class\Mathematics\Polygon.h"
#include "Class\Game\Utill\stdafx.h"
#include "Class\Game\Utill\Config.h"

class CBox2D :
	public CPolygon
{
public:
	CBox2D();
	CBox2D(RECT);
	CBox2D(RECT, vector2d);
	CBox2D(LPDIRECT3DDEVICE9, RECT, vector2d);
	CBox2D(LPDIRECT3DDEVICE9, vector2d, vector2d, vector2d);
	CBox2D(float, float, float, float);
	CBox2D(float, float, float, float, vector2d);
	~CBox2D();

	static		bool	Intersect(CBox2D, CBox2D);

	virtual		void	update(float deltaTime, vector2d pos)			override;
	virtual		void	render()										override;

				float	getX();				void	setX(float);
				float	getY();				void	setY(float);
				float	getWidth();			void	setWidth(float);
				float	getHeight();		void	setHeight(float);
				float	getVelocityX();		void	setVelocityX(float);
				float	getVelocityY();		void	setVelocityY(float); 
				vector2d getVelocity();		void setVelocity(vector2d);

private:
	vector2d	m_Position;
	vector2d	m_Size;
	vector2d	m_Velocity;

	int			m_StyleBoddy;

private:
	LPD3DXLINE	m_line;

};

#endif