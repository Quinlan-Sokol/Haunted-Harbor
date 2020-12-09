#pragma once
#include "weaponsobject.h"
#include "atlimage.h"
class EnemyObject :public WeaponsObject
{
public:

	EnemyObject(CString filename, int posX, int posY): WeaponsObject(filename, posX, posY)
	{
		speedX = 0;
		speedY = 0;
		isDead = false;
	}
	int speedX;
	int speedY;
	int isDead;
	virtual void onHit(BulletObject *b) = 0;
	virtual void move() = 0;
	virtual void checkCollisionWithBlock(GraphicsObject *block) = 0;
	~EnemyObject(void)
	{
	}
};

