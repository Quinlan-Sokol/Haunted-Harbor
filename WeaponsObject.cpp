#include "stdafx.h"
#include "WeaponsObject.h"
#include <cmath>


WeaponsObject::WeaponsObject(CString filename, int posX, int posY): GraphicsObject(filename, posX, posY)
{

}
void WeaponsObject::moveBullet()
{
	for(int i = 0; i < numBullets; i++)
	{
		if(bullets[i]->isFired)
		{
			bullets[i]->move();
		}
	}
}
void WeaponsObject::drawBullet(HDC offScreenDC)
{
	for(int i = 0; i < numBullets; i++)
	{
		if(bullets[i]->isFired)
		{
			bullets[i]->draw(offScreenDC);
		}
	}
}
void WeaponsObject::fireBullet(int x, int y, int xs, int ys)
{
	for(int i = 0; i < numBullets; i++)
	{
		if(!bullets[i]->isFired)
		{
			bullets[i]->x = x;
			bullets[i]->y = y;
			bullets[i]->speedX = xs;
			bullets[i]->speedY = ys;

			bullets[i]->isFired = true;
			bullets[i]->distanceMoved =0;

			break;
		}
	}
}
void WeaponsObject::checkBulletCollisionWithBlock(GraphicsObject *block)
{
	for(int i = 0; i < numBullets; i++)
	{
		if(bullets[i]->isFired)
		{
			if(bullets[i]->hitTest(block) && bullets[i]->exploding == false)
			{
				if(abs(bullets[i]->x - block->x) < abs(bullets[i]->x - (block->x+block->width)))
				{
					bullets[i]->x = block->x;
				}
				else if(abs(bullets[i]->x - block->x) > abs(bullets[i]->x - (block->x+block->width)))
				{
					bullets[i]->x = block->x + block->width;
				}
				bullets[i]->setExplode();
			}
		}
	}
}
void WeaponsObject::checkBulletCollisionWithObject(WeaponsObject *object)
{
	for(int i = 0; i < numBullets; i++)
	{
		if(bullets[i]->isFired && bullets[i]->exploding == false)
		{
			if(bullets[i]->hitTest(object))
			{
				object->onHit(bullets[i]);
				bullets[i]->setExplode();
			}
		}
	}
}

WeaponsObject::~WeaponsObject(void)
{
}
