#pragma once
#include "BulletObject.h"
class PurpleBullet: public BulletObject
{
public:
	PurpleBullet(void);
	void setExplode();
	void reset();
	~PurpleBullet(void);
};

