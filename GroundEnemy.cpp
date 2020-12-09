dfsssssssssss#include "stdafx.h"
#include "GroundEnemy.h"
#include "GreenBullet.h"


GroundEnemy::GroundEnemy(void): EnemyObject("../pics/SkullCrab.bmp", 0,0)
{
	width = 28;
	height = 35;
	hitWidth = width;
	hitHeight = height;
	speedX = -5;
	speedY = 0;
	curCell = 0;
	startCell = 0;
	endCell = 10;
	loopCells = true;
	isDead = false;//CHANGE BACK LATER****************************************************************************************
	
	numBullets = 5;
	for(int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet();
	}
}
void GroundEnemy::move()
{
	prevX = x;
	prevY = y;
	x += speedX;
	y += speedY;
	
	speedY += GRAVITY;
	if(y > GROUND - height)
	{
		y = GROUND - height;
		speedY = 0;
	}
	if(!isDead){
		int rng = rand()%30;
		if(rng == 1)
		{
			if(speedX < 0)
			{
				fireBullet(x+10, y+20, -10, 0);
			}
			else if(speedX > 0)
			{
				fireBullet(x+10, y+20, 10, 0);
			}
		}
	}
	animate();
}
void GroundEnemy::onHit(BulletObject *b)
{
	x += b->speedX;
	curCell = 0;
	endCell = 0;
	if(speedX < 0)
	{
		picY = 70;
	}
	else if(speedX > 0)
	{
		picY = 105;
	}
	isDead = true;
	speedX = 0;
}
void GroundEnemy::checkCollisionWithBlock(GraphicsObject *block)
{
	if(hitTest(block))
	{
		if(prevX + hitWidth <= block->x)
		{//from blocks left
			speedX *= -1;
			x = block->x - hitWidth;
			picY = 0;
		}
		else if(prevX >= block->x + block->hitWidth)
		{//from blocks right
			speedX *= -1;
			x = block->x + block->hitWidth;
			picY = 35;
		}
		else if(prevY + hitHeight <= block->y)
		{//from blocks top
			speedY = 0;
			y= block->y - hitHeight;
		}
		else if(prevY >= block->y - block->hitHeight)
		{//from block bottom
			speedY = 0;
			y= block->y + hitHeight;
		}
	}
}

