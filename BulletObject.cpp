#include "stdafx.h"
#include "BulletObject.h"
#include <math.h>

BulletObject::BulletObject(CString filename): GraphicsObject(filename, 0, 0)
{
	isFired = false;
	height = 12;
	width = 12;
	hitHeight = height;
	hitWidth = width;
	distanceMoved = 0;
	maxDistance = 300;
	exploding = false;
	speedX = 0;
	speedY = 0;
	damage = 10;
}
void BulletObject::reset()
{

}
void BulletObject::move()
{
	animate();
	if(exploding)
	{
		if(curCell == endCell){
			reset();
		}
	}
	else
	{
		x += speedX;
		y += speedY;
		distanceMoved += abs(speedX) + abs(speedY);
		if(distanceMoved > maxDistance)
		{
			isFired = false;
			distanceMoved = 0;
		}
	}
}
void BulletObject::setExplode()
{

}
BulletObject::~BulletObject(void)
{
}
