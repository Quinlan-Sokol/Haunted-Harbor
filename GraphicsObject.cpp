#include "stdafx.h"
#include "GraphicsObject.h"


GraphicsObject::GraphicsObject(CString filename, int posX, int posY, int w, int h)  
{
	ID = filename;
	width = w;
	height = h;
	hitHeight = height;
	hitWidth = width;
	x = posX;
	y= posY;
	picX = 0;
	picY = 0;
	curCell = 0;
	startCell = 0;
	endCell = 0;
	loopCells = true;
	image.Load(ID);
}
void GraphicsObject::draw(HDC offScreenDC)
{
	image.SetTransparentColor(RGB(255, 174, 201));
	image.TransparentBlt(offScreenDC, x - mapPosition ,y, width, height, picX, picY, width, height);
}
void GraphicsObject::animate()
{
	curCell += 1;
	
	if(curCell >= endCell)
	{
		//loop to beginning
		if(loopCells)
		{
			curCell = startCell;
		}
		else
		{
			curCell = endCell;
		}
		
	}
	//update drawing position
	picX = width * curCell;
}
bool GraphicsObject::hitTest(GraphicsObject *object)
{
	if((x + hitWidth > object->x) && (x < object->x + object-> hitWidth))
	{
		if((y + hitHeight > object->y) && (y < object->y + object->hitHeight))
		{
			return true;
		}
	}
	return false;
}
void GraphicsObject::moveBlock(int newX, int newY)
{
	x = newX;
	y = newY;
}

GraphicsObject::~GraphicsObject(void)
{

}
