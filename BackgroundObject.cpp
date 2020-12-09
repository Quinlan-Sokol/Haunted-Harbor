#include "stdafx.h"
#include "BackgroundObject.h"


BackgroundObject::BackgroundObject(CString filename, int posX, int posY, int w, int h, double ss): GraphicsObject(filename, posX, posY)
{
	height = h;
	width = w;
	scrollSpeed = ss;
}
void BackgroundObject::draw(HDC offScreenDC)
{
	CImage image;
	int relativeX = (int)((x - mapPosition) * scrollSpeed) % width;

	image.Load(ID);
	image.SetTransparentColor(RGB(255, 174, 201));
	image.TransparentBlt(offScreenDC, relativeX ,y, width, height, 0, 0, width, height);
	image.TransparentBlt(offScreenDC, relativeX + width ,y, width, height, 0, 0, width, height);
	image.TransparentBlt(offScreenDC, relativeX - width ,y, width, height, 0, 0, width, height);
}

BackgroundObject::~BackgroundObject(void)
{
}
