#pragma once
#include "GraphicsObject.h"
#include "BulletObject.h"
class WeaponsObject: public GraphicsObject
{
public:
	WeaponsObject(CString filename, int posX, int posY);
	int numBullets;
	BulletObject *bullets[50];
	void fireBullet(int x, int y, int xs, int ys);
	void drawBullet(HDC offScreenDC);
	void moveBullet();
	void checkBulletCollisionWithBlock(GraphicsObject *block);
	void checkBulletCollisionWithObject(WeaponsObject *object);
	virtual void onHit(BulletObject *b){};
	~WeaponsObject(void);
};

