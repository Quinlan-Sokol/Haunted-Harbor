#include "stdafx.h"
#include "BossEnemy.h"
#include "GreenBullet.h"

BossEnemy::BossEnemy(PlayerObject *v): EnemyObject("../pics/LighthouseKeeper.bmp", 3000, 200)
{
	victor = v;
	width = 50;
	height = 86;
	hitWidth = width;
	hitHeight = height;
	count = 0;
	speedX = -3;
	speedY = 0;
	curCell = 0;
	startCell = 0;
	endCell = 11;
	offset = 68;
	loc = 1;
	loopCells = true;
	isDead = false;
	d1 = true;
	d2 = true;
	phase3 = false;
	bSpeedY = 0;
	bSpeedX = 0;
	b = 0;
	picX = 68;
	picY = 59;
	totalHealth = 500;
	currentHealth = totalHealth;
	numBullets = 10;
	for(int i = 0; i < numBullets; i++)
	{
		bullets[i] = new GreenBullet();
	}
}
void BossEnemy::onHit(BulletObject *b)
{
	currentHealth -= b->damage;
	if(currentHealth <= 0)
	{
		startCell = 0;
		width = 0;
		height = 0;
		endCell = 11;
		curCell = 0;
		picX = 0;
		picY = 0;
		loopCells = false;
		isDead = true;
		for(int i = 0; i < numBullets; i++)
		{
			bullets[i]->y = -300;
		}
	}
	if(!d2){
		switch(loc)
		{
			case 1:
				x = 2700;
				y = 200;
				speedX = 0;
				break;
			case 2:
				x = 3000;
				y = 200;
				speedX = 0;
				break;
		}
		if(x == 2700){
			loc = 2;
		}
		else if(x == 3000){
			loc = 1;
		}
	}
}
void BossEnemy::checkCollisionWithBlock(GraphicsObject *block)
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
			y = block->y - hitHeight;
			speedY = 0;
		}
		else if(prevY >= block->y - block->hitHeight)
		{//from block bottom
			y = block->y + block->hitHeight + 1;
			speedY = 0;
		}
	}
}
void BossEnemy::animate()
{
	curCell += 1;
	if(curCell >= endCell)
	{
		//loop to beginning
		if(loopCells)
		{
			curCell = startCell;
		}
		else
		{
			curCell = endCell;
		}
		
	}
	//update drawing position
	picX = width * curCell + offset;
}
void BossEnemy::move()
{
	prevX = x;
	prevY = y;
	y += speedY;
	int counter = 0;
	int ground;

	if(phase3){
		ground = 287;
	}
	else{
		ground = GROUND;
	}

	speedY += GRAVITY;
	if(y > ground - height)
	{
		y = ground - height;
		speedY = 0;
	}
	if(!isDead && !phase3){
		if(victor->x >= x){
			x -= speedX;
		}
		else if(victor->x < x){
			x += speedX;
		}
	}
	if(!isDead){
		if(victor->x >= x){
			picY = 145;
		}
		else if(victor->x < x){
			picY = 59;
		}
	}
	if(hitTest(victor))
	{
		if(victor->currentHealth <= 0)
		{
			victor->reset();
		}
		else{
			victor->currentHealth -= 1;
		}
	}
	if(currentHealth <= 330){
		if(d1){
			width = 52;
			height = 89;
			startCell = 14;
			endCell = 16;
			curCell = 14;
			offset = 0;
			d1 = false;

		}
		
		if(currentHealth <= 165){
			if(d2){
				width = 43;
				height = 90;
				startCell = 13;
				endCell = 13;
				curCell = 13;
				offset = 68;
				d2 = false;
				phase3 = true;
				//x = 2850;
				//y = 225;
			}
			
		}
	}
	animate();
}
void BossEnemy::fire()
{
	for(int i = 0; i < 5; i++)
	{
		y += bSpeedY;
		bSpeedY += GRAVITY;

		b += 3;
		bSpeedX += b;

		if(loc == 1)
		{
			bSpeedX *= -1;
		}
		else if(loc == 2)
		{
			b *= -1;
		}

		fireBullet(x + width/2, y + height, bSpeedX, bSpeedY);
	}
	b = 0;
	bSpeedY = 0;
	bSpeedX = 0;
}
BossEnemy::~BossEnemy(void){}