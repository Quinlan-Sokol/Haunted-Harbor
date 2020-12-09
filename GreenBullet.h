#pragma once
#include "bulletobject.h"
class GreenBullet :public BulletObject
{
public:
	GreenBullet(void);
	void setExplode();
	void reset();
	~GreenBullet(void);
};

