#include "stdafx.h"
#include "LifeBar.h"


LifeBar::LifeBar(PlayerObject *v)
{
	victor = v;

}
void LifeBar::draw(HDC screen)
{
	int height = 80*(double)victor->currentHealth/victor->totalHealth;
	HBRUSH hbrRED, hbrWHITE;

	hbrRED = CreateSolidBrush(RGB(255,0,0));
	hbrWHITE = CreateSolidBrush(RGB(255,255,255));

	SelectObject(screen, hbrWHITE);
	Rectangle(screen, 10,10,20,90);
	SelectObject(screen, hbrRED);
	Rectangle(screen, 10,90-height,20,90);

	DeleteObject(hbrRED);
	DeleteObject(hbrWHITE);
}

LifeBar::~LifeBar(void)
{
}
