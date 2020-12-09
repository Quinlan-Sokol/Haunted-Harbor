#pragma once
#include "EnemyObject.h"
#include "PlayerObject.h"
class BossEnemy :public EnemyObject
{
public:
	BossEnemy(PlayerObject *v);
	PlayerObject *victor;
	int prevX;
	int prevY;
	int offset;
	int loc;
	int count;
	bool d1;
	bool d2;
	bool phase3;
	int totalHealth;
	int currentHealth;
	int b;
	int bSpeedY;
	int bSpeedX;
	void move();
	void animate();
	void fire();
	void onHit(BulletObject *b);
	void checkCollisionWithBlock(GraphicsObject *block);
	~BossEnemy(void);
};

