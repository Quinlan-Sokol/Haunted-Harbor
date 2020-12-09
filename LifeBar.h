#pragma once
#include "GraphicsObject.h"
#include "PlayerObject.h"
class LifeBar
{
public:
	LifeBar(PlayerObject *v);
	PlayerObject *victor;
	void draw(HDC screen);
	~LifeBar(void);
};

