#pragma once
#include "EnemyObject.h"
#include "PlayerObject.h"
class FlyingEnemyObject: public EnemyObject
{
public:
	FlyingEnemyObject(PlayerObject *v, int cx, int cy);
	PlayerObject *victor;
	int radius;
	int angle;
	int centerX;
	int centerY;
	int shootTick;
	int shootDelay;
	int totalHealth;
	int currentHealth;
	void move();
	void fire();
	void onHit(BulletObject *b);
	void checkCollisionWithBlock(GraphicsObject *block);
	~FlyingEnemyObject(void);
};

