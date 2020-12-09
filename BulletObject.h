#pragma once
#include "GraphicsObject.h"
class BulletObject: public GraphicsObject
{
public:
	BulletObject(CString filename);
	int speedX;
	int speedY;
	int maxDistance;
	int distanceMoved;
	int damage;
	bool isFired;
	bool exploding;
	void move();
	virtual void setExplode();
	virtual void reset();
	~BulletObject(void);
};

