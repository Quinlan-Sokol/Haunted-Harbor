#pragma once
#include "EnemyObject.h"
class GroundEnemy :public EnemyObject
{
public:
	GroundEnemy(void);
	int prevX;
	int prevY;
	void move();
	void onHit(BulletObject *b);
	void checkCollisionWithBlock(GraphicsObject *block);
	~GroundEnemy(void);
};

