#include "stdafx.h"
#include "FlyingEnemyObject.h"
#include "GreenBullet.h"
#include <math.h>

FlyingEnemyObject::FlyingEnemyObject(PlayerObject *v, int cx, int cy):EnemyObject("../pics/SeaHag.bmp", 200, 200)
{
	victor = v;
	centerX = cx;
	centerY = cy;
	height = 39;
	width = 28;
	hitHeight = height;
	hitWidth = width;
	curCell = 0;
	endCell = 4;
	startCell = 0;
	loopCells = true;
	speedX = 5;
	speedY = 0;
	numBullets = 20;
	radius = 20;
	angle = 0;
	shootDelay = 30;
	shootTick = 0;
	totalHealth = 30;
	currentHealth = totalHealth;
	isDead = false;//CHANGE BACK LATER****************************************************************************************

	for(int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet();
		bullets[i]->maxDistance = 400;
	}
}
void FlyingEnemyObject::move()
{
	if(!isDead){
		double radians = (double)(angle*3.14159)/180;
		x = centerX + radius*cos(radians);
		y = centerY + radius*sin(radians);
		angle += 10;

		shootTick++;
		if(shootTick == shootDelay)
		{
			fire();
			shootTick = 0;
		}
	}
	animate();
}
void FlyingEnemyObject::onHit(BulletObject *b)
{
	currentHealth -= b->damage;
	if(currentHealth <= 0)
	{
		startCell = 0;
		width = 32;
		height = 28;
		endCell = 6;
		curCell = 0;
		picX = 0;
		picY = 156;
		loopCells = false;
		isDead = true;
	}
}
void FlyingEnemyObject::checkCollisionWithBlock(GraphicsObject *block)
{

}
void FlyingEnemyObject::fire()
{
	double run = abs((x + width/2) - (victor->x + victor->width/2));//run
	double rise = abs((y + height) - (victor->y + victor->height/2));//rise
	int xside = 1;
	int yside = 1;
	if(victor->x < x)
	{//on left side
		xside = -1;
	}
	if(victor->y < y)
	{
		yside = -1;
	}

	if(run > rise)
	{
		fireBullet(x + width/2, y + height, 10 * xside, 10 * rise/run * yside);
	}
	else
	{
		fireBullet(x + width/2, y + height, 10 * rise/run * xside, 10 * yside);
	}
}

FlyingEnemyObject::~FlyingEnemyObject()
{
}
