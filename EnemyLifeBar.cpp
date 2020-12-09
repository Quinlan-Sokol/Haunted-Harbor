#include "stdafx.h"
#include "EnemyLifeBar.h"


EnemyLifeBar::EnemyLifeBar(BossEnemy *e)
{
	enemy = e;
}
void EnemyLifeBar::draw(HDC screen)
{
	int width = 400*(double)enemy->currentHealth/enemy->totalHealth;
	HBRUSH hbrRED, hbrWHITE;

	hbrRED = CreateSolidBrush(RGB(255,0,0));
	hbrWHITE = CreateSolidBrush(RGB(255,255,255));

	SelectObject(screen, hbrWHITE);
	Rectangle(screen, 100,10,500,40);
	SelectObject(screen, hbrRED);
	Rectangle(screen, 500 - width,10,500,40);

	DeleteObject(hbrRED);
	DeleteObject(hbrWHITE);
}

EnemyLifeBar::~EnemyLifeBar(void)
{
}
