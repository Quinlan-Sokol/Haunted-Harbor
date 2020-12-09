#pragma once
#include "GraphicsObject.h"
#include "WeaponsObject.h"
#include "GroundEnemy.h"

#define MOVERIGHT 1
#define MOVELEFT 2
#define STANDLEFT 3
#define STANDRIGHT 4
#define JUMPRIGHT 5
#define JUMPLEFT 6
#define SHOOTRIGHT 7
#define SHOOTLEFT 8

class PlayerObject: public WeaponsObject
{
public:
	PlayerObject(void);
	int speedX;
	int speedY;
	int state;
	int prevX;
	int prevY;
	int totalHealth;
	int currentHealth;
	bool stoppedRight;
	bool stoppedLeft;
	void move();
	void setMoveRight();
	void setMoveLeft();
	void setStandRight();
	void setStandLeft();
	void setJumpRight();
	void setJumpLeft();
	void setShootRight();
	void setShootLeft();
	bool isJumping();
	void reset();
	void checkCollisionWithBlock(GraphicsObject *block);
	void onHit(BulletObject *h);
	~PlayerObject(void);
};

