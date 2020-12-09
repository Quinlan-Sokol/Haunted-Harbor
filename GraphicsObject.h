#pragma once
class GraphicsObject
{
public:
	GraphicsObject(CString filename, int posX, int posY, int w = 55, int h = 42); 
	CString ID;
	CImage image;
	int height;
	int width;
	int x;
	int y;
	int picX;
	int picY;
	int curCell;
	int endCell;
	int startCell;
	int hitHeight;
	int hitWidth;
	bool loopCells;
	void draw(HDC offScreenDC);
	void animate();
	void moveBlock(int x, int y);
	bool hitTest(GraphicsObject *object);
	~GraphicsObject(void);
};

