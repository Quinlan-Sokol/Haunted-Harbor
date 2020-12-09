#pragma once
#include "GraphicsObject.h"
#include "BossEnemy.h"
class EnemyLifeBar
{
public:
	EnemyLifeBar(BossEnemy *e);
	BossEnemy *enemy;
	void draw(HDC screen);
	~EnemyLifeBar(void);
};

