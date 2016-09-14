/*********************************************/
/* CREATE BY MICHAEL LE AND SHIN XINH NHAT THE GIOI*/
/* 13/07/2015*/
/********************************************/

/*********************************************/
/* WARING : TOO MANY GET/SET FUNCTION. FIX BOX2D*/
/*********************************************/


#ifndef __SWEPTAABB_H__
#define __SWEPTAABB_H__

#include "Class\Game\Utill\stdafx.h"
#include "Box2D.h"


inline bool AABBCheck(CBox2D box1, CBox2D box2)
{
	return !(	box1.getX() + box1.getWidth() < box2.getX()	
			||	box1.getX() > box2.getX() + box2.getWidth() 
			||	box1.getY() + box1.getHeight() < box2.getY() 
			||	box1.getY() > box2.getY() + box2.getHeight());

}


inline CBox2D GetSweptBroadPhaseBox(CBox2D box, vector2d velocity)
{
	CBox2D boundingBox(0, 0, 0, 0);

	box.getVelocityX() > 0 ? boundingBox.setX(box.getX())									: boundingBox.setX(box.getX()			- box.getVelocityX());
	box.getVelocityY() > 0 ? boundingBox.setY(box.getY())									: boundingBox.setY(box.getY()			- box.getVelocityY());		// Because of changing axis to decac
	boundingBox.setWidth(box.getWidth()	+ box.getVelocityX());
	boundingBox.setHeight(box.getHeight()	+ box.getVelocityY());

	boundingBox.setVelocityX((velocity.x * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float) 1 / FPS));
	boundingBox.setVelocityY((velocity.y * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float) 1 / FPS));

	return boundingBox;
}

inline CBox2D GetBroadPhaseBox(CBox2D box, vector2d velocity)
{
	CBox2D boundingBox(0, 0, 0, 0, vector2dZero);

	boundingBox.setX(box.getX());
	boundingBox.setY(box.getY());
	boundingBox.setWidth(box.getWidth());
	boundingBox.setHeight(box.getHeight());

	boundingBox.setVelocityX((velocity.x * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float)1 / FPS));
	boundingBox.setVelocityY((velocity.y * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float)1 / FPS));

	return  GetSweptBroadPhaseBox(boundingBox, velocity);
}

inline CBox2D GetBoundForMovable(CBox2D box, vector2d velocity)
{
	CBox2D boundingBox(0, 0, 0, 0, vector2dZero);

	boundingBox.setX(box.getX());
	boundingBox.setY(box.getY());
	boundingBox.setWidth(box.getWidth());
	boundingBox.setHeight(box.getHeight());

	boundingBox.setVelocityX((velocity.x * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float)1 / FPS));
	boundingBox.setVelocityY((velocity.y * CTimer::getInstance()->getElapedTime() / 1000.0) / ((float)1 / FPS));

	return  boundingBox;
}

inline bool AABB(CBox2D box1, CBox2D box2, float& moveX, float& moveY)
{
	moveX	=	moveY	=	0.0f;

	float xInvEntry		= box2.getX() - (box1.getX()	 + box1.getWidth());
	float xInvExit		= box2.getX() + box2.getWidth()  - box1.getX();
	float yInvEntry		= box2.getY() - box2.getHeight() - box1.getY();
	float yInvExit		= box2.getY() - box1.getY() + box1.getHeight();

	// check that there was a collision
	if (xInvEntry > 0 || xInvExit < 0 || yInvEntry > 0 || yInvExit < 0)
		return false;

	// find the offset of both sides
	moveX = abs(xInvEntry)	< xInvExit ? xInvEntry : xInvExit;
	moveY = abs(yInvEntry)	< yInvExit ? yInvEntry : yInvExit;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;

}


//SweptAABB Alogorithm
inline float SweptAABB(CBox2D box1, CBox2D box2, float &normalX, float &normalY)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	if (box1.getVelocityX() > 0.0f)
	{
		xInvEntry		= box2.getX()	- (box1.getX()		+ box1.getWidth());
		xInvExit		= (box2.getX()	+ box2.getWidth())	- box1.getX();
	}
	else
	{
		xInvEntry		= (box2.getX()	+ box2.getWidth())	- box1.getX();
		xInvExit		= box2.getX()	- (box1.getX()		+ box1.getWidth());
	}

	if (box1.getVelocityY() > 0.0f)
	{
		yInvEntry		= (box2.getY()	- box2.getHeight())	- box1.getY();
		yInvExit		= box2.getY()	- (box1.getY()		- box1.getHeight());
	}
	else
	{
		yInvEntry		= box2.getY()	- (box1.getY()		- box1.getHeight());
		yInvExit		= (box2.getY()	- box2.getHeight())	- box1.getY();
	}


	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.getVelocityX() == 0.0f)
	{
		xEntry			= -std::numeric_limits<float>::infinity();
		xExit			=  std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry			= xInvEntry	/ box1.getVelocityX();
		xExit			= xInvExit	/ box1.getVelocityX();
	}

	if (box1.getVelocityY() == 0.0f)
	{
		yEntry			= -std::numeric_limits<float>::infinity();
		yExit			=  std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry			= yInvEntry	/ box1.getVelocityY();
		yExit			= yInvExit	/ box1.getVelocityY();
	}

	float entryTime		= std::fmaxf(xEntry, yEntry);
	float exitTime		= std::fminf(xExit, yExit);

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || yEntry > 1.0f || yEntry > 1.0f)
	{
		normalX			= 0.0f;
		normalY			= 0.0f;
		return 1.0f;
	}
	else
	{
		if (xEntry > yEntry && (box1.getY() - box1.getHeight() != box2.getY()))
		{
			if (xInvEntry < 0.0f)
			{
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else
			{
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else
		{
			if (yInvEntry <= 0.0f)
			{
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else
			{
				normalX = 0.0f;
				normalY = -1.0f;
			}
		}

		return entryTime;
	}
}

#endif