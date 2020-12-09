#include "stdafx.h"
#include "PurpleBullet.h"


PurpleBullet::PurpleBullet():BulletObject("../pics/PurpleFire.bmp")
{
	height = 12;
	width = 12;
	hitHeight = 12;
	hitWidth = 12;
	damage = 15;
}
void PurpleBullet::setExplode()
{
	picY = 12;
	picX = 0;
	width = 32;
	height = 32;
	x -= 12;
	y -= 12;
	loopCells = false;
	endCell = 2;
	curCell = 0;
	exploding = true;
}
void PurpleBullet::reset()
{
	isFired = false;
	height = 12;
	width = 12;
	distanceMoved = 0;
	exploding = false;
	picX = 0;
	picY = 0;
	curCell = 0;
	endCell = 0;
}

PurpleBullet::~PurpleBullet(void)
{
}
