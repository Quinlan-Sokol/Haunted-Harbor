#pragma once
#include "GraphicsObject.h"
class BackgroundObject: public GraphicsObject
{
public:
	BackgroundObject(CString filename, int posX, int posY, int h, int w, double ss);
	double scrollSpeed;
	void draw(HDC offScreenDC);
	~BackgroundObject(void);
};

