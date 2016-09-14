#ifndef __SWEPTAABB_H__
#define __SWEPTAABB_H__

#include "Class\Game\Utill\stdafx.h"
#include "Box2D.h"
#include "d3d9.h"
#include <limits>

using namespace std;

static CBox2D GetSweptBroadPhaseBox(CBox2D b)
{
	CBox2D broadphasebox(0, 0, 0, 0);

	b.getVelocityX() > 0 ? broadphasebox.setX(b.getX()) : broadphasebox.setX(b.getX() + b.getVelocityX());
	b.getVelocityY() > 0 ? broadphasebox.setY(b.getY() + b.getVelocityY()) : broadphasebox.setY(b.getY()); // Because of changing axis to decac
	b.getVelocityX() > 0 ? broadphasebox.setWidth(abs(b.getWidth() + b.getVelocityX())) : broadphasebox.setWidth(abs(b.getWidth() - b.getVelocityX()));
	b.getVelocityY() > 0 ? broadphasebox.setHeight(abs(b.getHeight() + b.getVelocityY())) : broadphasebox.setWidth(abs(b.getHeight() - b.getVelocityY()));
	return broadphasebox;
}

static COLDIRECTION CheckAABB(CBox2D box1, CBox2D box2)
{
	float _left = box1.getX() - (box2.getX() + box2.getWidth());
	float _right = (box1.getX() + box1.getWidth()) - box2.getX();
	float _top = box2.getY() - (box1.getY() - box1.getHeight());
	float _bottom = (box2.getY() - box2.getHeight()) - box1.getY();

	float minX = min(abs(_left), abs(_right));
	float minY = min(abs(_top), abs(_bottom));

	if (_left <= 0 && _right >= 0 && _top >= 0 && _bottom <= 0)
	{
		if (minX < minY)
		{
			if (box1.getX() < box2.getX())return COLDIRECTION::COLDIRECTION_RIGHT;
			if (box1.getX() > box2.getX())return COLDIRECTION::COLDIRECTION_LEFT;
		}
		else
		{
			if (box1.getY() < box2.getY())return COLDIRECTION::COLDIRECTION_TOP;
			if (box1.getY() > box2.getY()) return COLDIRECTION::COLDIRECTION_BOTTOM;
		}
	}

	return COLDIRECTION::COLDIRECTION_NONE;

}
inline float SweptAABB(CBox2D box1, CBox2D box2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInExit;

	if (box1.getVelocityX() > 0.0f)
	{
		xInvEntry = box2.getX() - (box1.getX() + box1.getWidth());
		xInvExit = (box2.getX() + box2.getWidth()) - box1.getX();
	}
	else
	{
		xInvEntry = (box2.getX() + box2.getWidth()) - box1.getX();
		xInvExit = box2.getX() - (box1.getX() + box1.getWidth());
	}

	/*if (box1.getVelocityY() > 0.0f)
	{
	yInvEntry = box2.getY() - (box1.getY() + box1.getHeight());
	yInExit = (box2.getY() + box2.getHeight()) - box1.getY();
	}
	else
	{
	yInvEntry = (box2.getY() + box2.getHeight()) - box1.getY();
	yInExit = box2.getY() - (box1.getY() + box1.getHeight());
	}*/


	if (box1.getVelocityY() > 0.0f)
	{
		yInvEntry = (box2.getY() - box2.getHeight()) - box1.getY();
		yInExit = box2.getY() - (box1.getY() - box1.getHeight());
	}
	else
	{
		yInvEntry = box2.getY() - (box1.getY() - box1.getHeight());
		yInExit = (box2.getY() - box2.getHeight()) - box1.getY();
	}


	// xác định thời gian va chạm
	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.getVelocityX() == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = (float)xInvEntry / box1.getVelocityX();
		xExit = (float)xInvExit / box1.getVelocityX();
	}

	if (box1.getVelocityY() == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = (float)yInvEntry / box1.getVelocityY();
		yExit = (float)yInExit / box1.getVelocityY();
	}

	//tìm thời gian bắt đầu va chạm
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	//Các trường hợp không có va chạm

	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else //có va chạm
	{
		if (xEntry > yEntry)
		{
			if (xEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
		return entryTime;
	}
}

//
//inline float SweptAABB(CBox2D box1, CBox2D box2, float& normalx, float& normaly)
//{
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInExit;
//
//
//	if (box1.getVelocityY() > 0.0f)
//	{
//		yInvEntry = box2.getY() - (box1.getY() + box1.getHeight());
//		yInExit = (box2.getY() + box2.getHeight()) - box1.getY();
//	}
//	else
//	{
//		yInvEntry = (box2.getY() + box2.getHeight()) - box1.getY();
//		yInExit = box2.getY() - (box1.getY() + box1.getHeight());
//	}
//
//
//	if (box1.getVelocityX() > 0.0f)
//	{
//		xInvEntry = box2.getX() - (box1.getX() + box1.getWidth());
//		xInvExit = (box2.getX() + box2.getWidth()) - box1.getX();
//	}
//	else
//	{
//		xInvEntry = (box2.getX() + box2.getWidth()) - box1.getX();
//		xInvExit = box2.getX() - (box1.getX() + box1.getWidth());
//	}
//
//
//
//
//	// xác định thời gian va chạm
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (box1.getVelocityX() == 0.0f)
//	{
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = (float)xInvEntry / box1.getVelocityX();
//		xExit = (float)xInvExit / box1.getVelocityX();
//	}
//
//	if (box1.getVelocityY() == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = (float)yInvEntry / box1.getVelocityY();
//		yExit = (float)yInExit / box1.getVelocityY();
//	}
//
//	//tìm thời gian bắt đầu va chạm
//	float entryTime = max(xEntry, yEntry);
//	float exitTime = min(xExit, yExit);
//
//	//Các trường hợp không có va chạm
//
//	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else //có va chạm
//	{
//		if (xEntry > yEntry)
//		{
//			if (xEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yEntry < 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		}
//		return entryTime;
//	}
//}
#endif