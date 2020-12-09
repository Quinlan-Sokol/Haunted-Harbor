#include "stdafx.h"
#include "PlayerObject.h"
#include "PurpleBullet.h"


PlayerObject::PlayerObject(void): WeaponsObject("../Pics/ViktorTesla.bmp", 100, 100)
{
	setStandRight();
	speedX = 0;
	speedY = 0;
	currentHealth = 100;
	totalHealth = 100;
	state = STANDRIGHT;
	numBullets = 10;
	for(int i = 0; i < numBullets; i++)
	{
		bullets[i] = new PurpleBullet();
	}
	hitWidth = 54;
	hitHeight = 42;
	
}
void PlayerObject::move()
{
	prevX = x;
	prevY = y;

	x += speedX;
	y += speedY;
	speedY += GRAVITY;
	if(y > GROUND - height)
	{
		if(state == JUMPLEFT && stoppedLeft)
		{
			setStandLeft();
		}
		else if(state == JUMPRIGHT && stoppedRight)
		{
			setStandRight();
		}
		else if(state == JUMPLEFT && !stoppedLeft)
		{
			setMoveLeft();
		}
		else if(state == JUMPRIGHT  && !stoppedRight)
		{
			setMoveRight();
		}

		y = GROUND - height;
		speedY = 0;
	}
	if((x - mapPosition < 100 && speedX < 0) || (x - mapPosition > 350 && speedX > 0))
	{
		mapPosition += speedX;
	}
	animate();
}



void PlayerObject::setMoveRight()
{
	width = 54;
	height = 42;
	picY = 0;
	endCell = 9;
	loopCells = true;
	startCell = 1;
	speedX = 10;
	picX = 60;
	state = MOVERIGHT;
}
void PlayerObject::setMoveLeft()
{
	width = 54;
	height = 42;
	picY = 42;
	endCell = 9;
	loopCells = true;
	startCell = 1;
	speedX = -10;
	state = MOVELEFT;
}
void PlayerObject::setStandRight()
{
	curCell = 0;
	width = 54;
	height = 42;
	picY = 0;
	endCell = 0;
	loopCells = false;
	startCell = 0;
	speedX = 0;
	state = STANDRIGHT;
}
void PlayerObject::setStandLeft()
{
	curCell = 0;
	width = 54;
	height = 42;
	picY = 42;
	endCell = 0;
	loopCells = false;
	startCell = 0;
	speedX = 0;
	state = STANDLEFT;
}
void PlayerObject::setJumpRight()
{
	curCell = 0;
	width = 48;
	height = 56;
	picY = 86;
	endCell = 5;
	loopCells = false;
	speedY = -30;
	state = JUMPRIGHT;
}
void PlayerObject::setJumpLeft()
{
	curCell = 0;
	width = 48;
	height = 56;
	picY = 146;
	endCell = 5;
	loopCells = false;
	speedY = -30;
	state = JUMPLEFT;
}
void PlayerObject::setShootRight()
{
	curCell = 0;
	width = 60;
	height = 38;
	picY = 199;
	endCell = 0;
	loopCells = false;
	startCell = 0;
	speedX = 0;
	state = SHOOTRIGHT;
}
void PlayerObject::setShootLeft()
{
	curCell = 0;
	width = 60;
	height = 38;
	picY = 237;
	endCell = 0;
	loopCells = false;
	startCell = 0;
	speedX = 0;
	state = SHOOTLEFT;
}
bool PlayerObject::isJumping()
{
	return(state == JUMPLEFT || state == JUMPRIGHT);
}
void PlayerObject::checkCollisionWithBlock(GraphicsObject *block)
{
	if(hitTest(block))
	{
		if(prevX + hitWidth <= block->x)
		{//from blocks left
			x = block->x - hitWidth;
		}
		else if(prevX >= block->x + block->hitWidth)
		{//from blocks right
			x = block->x + block->hitWidth;
		}
		else if(prevY + hitHeight <= block->y)
		{//from blocks top
			if(state == JUMPLEFT && stoppedLeft == true)
			{
				setStandLeft();
			}
			else if(state == JUMPRIGHT && stoppedRight == true)
			{
				setStandRight();
			}
			else if(state == JUMPLEFT && stoppedLeft == false)
			{
				setMoveLeft();
			}
			else if(state == JUMPRIGHT && stoppedRight == false)
			{
				setMoveRight();
			}
			y = block->y - hitHeight;
			speedY = 0;
		}
		else if(prevY >= block->y - block->hitHeight)
		{//from block bottom
			y = block->y + block->hitHeight + 1;
			speedY = 0;
		}
		if(y + hitHeight > GROUND)
		{//cheap work-around
			y -= hitHeight;
		}
	}
}
void PlayerObject::onHit(BulletObject *b)
{
	x += b->speedX;

	//speedY = -20;
	currentHealth -= b->damage;
	if(currentHealth <= 0)
	{
		reset();
	}
}
void PlayerObject::reset()
{
	x = 100;
	y = 100;
	speedY = 0;
	speedX = 0;
	setStandRight();
	state = STANDRIGHT;
	currentHealth = totalHealth;
	mapPosition = 0;
}
PlayerObject::~PlayerObject(void)
{
}
