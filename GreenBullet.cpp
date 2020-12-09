#include "stdafx.h"
#include "GreenBullet.h"


GreenBullet::GreenBullet(void):BulletObject("../pics/GreenFire.bmp")
{
	height = 7;
	width = 7;
	hitHeight = 7;
	hitWidth = 7;
}
void GreenBullet::setExplode()
{
	picY = 8;
	picX = 0;
	width = 15;
	height = 15;
	x -= 8;
	y -= 8;
	loopCells = false;
	endCell = 2;
	curCell = 0;
	exploding = true;
}
void GreenBullet::reset()
{
	isFired = false;
	height = 7;
	width = 7;
	endCell = 0;
	distanceMoved = 0;
	exploding = false;
	picX = 0;
	picY = 0;
	curCell = 0;
	endCell = 0;
}

GreenBullet::~GreenBullet(void)
{
}
