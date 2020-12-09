// Haunted Harbor.cpp : Defines the entry point for the application.
//
#pragma warning(disable:4996)

#include "stdafx.h"
#include "Haunted Harbor.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackgroundObject.h"
#include "GroundEnemy.h"
#include "EnemyObject.h"
#include "FlyingEnemyObject.h"
#include "LifeBar.h"
#include "EnemyLifeBar.h"
#include "BossEnemy.h"
#include <Windowsx.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <Mmsystem.h>

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void setScreen();
void drawScreen(HWND hWnd);
void loadMap();

PlayerObject victor;
LifeBar lifebar(&victor);
BossEnemy enemy(&victor);
EnemyLifeBar enemylifebar(&enemy);
BackgroundObject background("../Pics/Background3.jpg", 0, 0, 5118, 800, 0.2);
BackgroundObject startscreen("../pics/TitleScreen.jpg", 0, 0, 700, 550, 0);
BackgroundObject ground("../Pics/Ground.bmp", 0, GROUND, 774, 128, 1);
GraphicsObject *blockArray[100];
EnemyObject *enemyArray[100];

int deaths = 0;
int numBlocks = 0;
int numEnemies = 0;
int mapPosition = 0;
int loc = 1;
int counter = 0;
int counter2 = 0;
bool canFire = true;
bool startGame = false;
bool d1 = true;
bool d2 = true;
HDC offScreenDC;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HAUNTEDHARBOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HAUNTEDHARBOR));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAUNTEDHARBOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HAUNTEDHARBOR);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 580, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   int x = 0;


   loadMap();

   PlaySound("../Music/ghostMusic.wav", NULL, SND_LOOP | SND_ASYNC);

   SetTimer(hWnd, 1, 50, NULL);

   setScreen();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	static wchar_t text1[] = L"Use WASD to move and jump";
	static wchar_t text2[] = L"Press space to shoot";
	static wchar_t text3[] = L"Boss Health";
	/*
	
	std::wstring t = L"Deaths";
	std::wstring t2;
	t2 = t + std::to_wstring(deaths);
	const wchar_t* text3 = t2.c_str();*/

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
			case 0x44:
				if(victor.isJumping())
				{
					victor.picY = 86;
					victor.speedX = 10;
					victor.state = JUMPRIGHT;
				}
				else
				{
					victor.setMoveRight();
				}
				victor.stoppedRight = false;
				break;
			case 0x41:
				if(victor.isJumping())
				{
					victor.picY = 146;
					victor.speedX = -10;
					victor.state = JUMPLEFT;
				}
				else
				{
					victor.setMoveLeft();
				}
				victor.stoppedLeft = false;
				break;
			case 0x57:
				if(victor.state == MOVERIGHT || victor.state == STANDRIGHT)
				{
					victor.setJumpRight();
				}
				else if(victor.state == MOVELEFT || victor.state == STANDLEFT)
				{
					victor.setJumpLeft();
				}
				break;
			case VK_SPACE:
				if(canFire)
				{
					if(victor.state == STANDRIGHT)
					{
						victor.setShootRight();
					}
					else if(victor.state == STANDLEFT)
					{
						victor.setShootLeft();
					}
					if(victor.state == SHOOTLEFT || victor.state == MOVELEFT || victor.state == JUMPLEFT || victor.state == STANDLEFT)
					{
						victor.fireBullet(victor.x, victor.y + 10, -20 + victor.speedX, 0);
					}
					else
					{
						victor.fireBullet(victor.x + victor.width -15, victor.y + 10, 20 + victor.speedX, 0);
					}
					canFire = false;
					break;
				}
		}
		break;
	case VK_LEFT:
		mapPosition -= 2;
	case VK_RIGHT:
		mapPosition += 2;
	case WM_TIMER:
		if(startGame)
		{
			victor.move();
			victor.moveBullet();
			for(int i = 0; i < numBlocks; i++)
			{
				victor.checkCollisionWithBlock(blockArray[i]);
				victor.checkBulletCollisionWithBlock(blockArray[i]);
				enemy.checkCollisionWithBlock(blockArray[i]);
				enemy.checkBulletCollisionWithBlock(blockArray[i]);
			}
			if(!enemy.isDead)
			{
				enemy.move();
				enemy.moveBullet();
				victor.checkBulletCollisionWithObject(&enemy);
				enemy.checkBulletCollisionWithObject(&victor);
			}
			for(int i = 0; i < numEnemies; i++)
			{
				enemyArray[i]->move();
				enemyArray[i]->moveBullet();
				if(!enemyArray[i]->isDead)
				{
					enemyArray[i]->checkBulletCollisionWithObject(&victor);
					victor.checkBulletCollisionWithObject(enemyArray[i]);
				}
				for(int j = 0; j < numBlocks; j++)
				{
					enemyArray[i]->checkCollisionWithBlock(blockArray[j]);
					enemyArray[i]->checkBulletCollisionWithBlock(blockArray[j]);
				}
			}
			if(victor.currentHealth <= 0){
				deaths++;
			}
			bool checkDead = true;
			for(int i = 0; i < 21;i++)
			{
				if(enemyArray[i]->isDead == false)
				{
					checkDead = false;
				}
			}
			if(checkDead){
				blockArray[53]->moveBlock(0, -200);
			}
			if(victor.x >= 2700){
				
				if(d1){
					PlaySound(NULL, NULL, 0);
					PlaySound("../Music/BossBattle.wav", NULL, SND_LOOP | SND_ASYNC);
					d1 = false;
				}
				
			}
			if(enemy.currentHealth <= 330 && enemy.currentHealth > 165)
			{
				if(d2)
				{
					blockArray[64]->moveBlock(0, -200);
					d2 = false;
				}
			}
			if(enemy.phase3 && !enemy.isDead)
			{
				if(counter2 == 20)
				{
					enemy.fire();
					counter2 = 0;
				}
				counter2++;
			}
		}
		
		PostMessage(hWnd, WM_PAINT, 0,0);
		if(!canFire){
			if(counter >= 8){
				canFire = true;
				counter = 0;
			}
			counter++;
		}
	case WM_KEYUP:
		switch(wParam)
		{
			case 0x44:
				if(!victor.isJumping())
				{
					victor.setStandRight();
				}
				victor.stoppedRight = true;
				break;
			case 0x41:
				if(!victor.isJumping())
				{
					victor.setStandLeft();
				}
				victor.stoppedLeft = true;
				break;
			case VK_SPACE:
				if(victor.state == SHOOTRIGHT)
				{
					victor.setStandRight();
				}
				else if(victor.state == SHOOTLEFT)
				{
					victor.setStandLeft();
				}
				
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int x = GET_X_LPARAM(lParam); 
			int y = GET_Y_LPARAM(lParam);
			if(y > 460 && y < 490){
				if(x > 320 && x < 400){
					if(!startGame){
						startGame = true;
					}
				}
			}
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		if(startGame)
		{
			background.draw(offScreenDC);
			ground.draw(offScreenDC);
			victor.draw(offScreenDC);
			for(int i = 0; i < numBlocks; i++){
				blockArray[i]->draw(offScreenDC);
			}
			for(int i = 0; i < numEnemies; i++){
			
				enemyArray[i]->draw(offScreenDC);
				enemyArray[i]->drawBullet(offScreenDC);
			}
			lifebar.draw(offScreenDC);
			victor.drawBullet(offScreenDC);
			enemy.drawBullet(offScreenDC);
			enemy.draw(offScreenDC);
			if(!enemy.isDead && d1 == false){
				enemylifebar.draw(offScreenDC);
				TextOut(offScreenDC, 225, 16, (LPCSTR)text3, wcslen(text2) + 2);
			}

			TextOut(offScreenDC, 0, 450, (LPCSTR)text1, wcslen(text1) + 8);
			TextOut(offScreenDC, 0, 466, (LPCSTR)text2, wcslen(text2) + 20);
			
			//t2 = t + std::to_wstring(deaths);
			//const wchar_t* text3 = t2.c_str();
			//TextOut(offScreenDC, 50, 0, (LPCSTR)text3, wcslen(text3) + 8);
		}
		else{
			startscreen.draw(offScreenDC);
		}
		drawScreen(hWnd);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		for(int i = 0; i < numEnemies; i++)
			delete enemyArray[i];
		for(int i = 0; i < numBlocks; i++)
			delete blockArray[i];
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
void setScreen()
{
	HDC hTempDC;
	HBITMAP offScreenBMP;
	hTempDC = GetDC(0);
	offScreenDC = CreateCompatibleDC(hTempDC);
	offScreenBMP = CreateCompatibleBitmap(hTempDC, 800, 600);
	SelectObject(offScreenDC, offScreenBMP);
	ReleaseDC(0, hTempDC);
}
void drawScreen(HWND hWnd)
{
	HDC ScreenDC;
	ScreenDC = GetDC(hWnd);
	TransparentBlt(ScreenDC,0,0,700,550,offScreenDC,0,0,700,550,RGB(255,174,201));
	DeleteDC(ScreenDC);
}
void loadMap()
{
	FILE *file;
	file = fopen("../Levels/Level1.txt", "r");

	char section[80];
	int index = 0, x = 0, y = 0;

	while (true)
	{
		fscanf(file, "%s", section);
		

		if (strcmp(section, "[Victor]") == 0)
		{
			while (true)
			{
				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1)
				{
					break;
				}

				victor.x = x;
				victor.y = y;
			}
		}

		if (strcmp(section, "[Little-Block]") == 0)
		{
			while (true)
			{
				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1)
				{
					break;
				}

				blockArray[numBlocks] = new GraphicsObject("../Pics/SmallCrate.bmp", x, y, 32, 32);
				numBlocks++;
			}
		}
		
		if (strcmp(section, "[Big-Block]") == 0)
		{
			while (true)
			{
				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1)
				{
					break;
				}

				blockArray[numBlocks] = new GraphicsObject("../Pics/Crate.bmp", x, y, 64, 64);
				numBlocks++;
			}
		}

		if (strcmp(section, "[Flying-Enemy]") == 0)
		{
			while (true)
			{
				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1)
				{
					break;
				}

				enemyArray[numEnemies] = new FlyingEnemyObject(&victor, x, y);
				enemyArray[numEnemies]->x = x;
				enemyArray[numEnemies]->y = y;
				numEnemies++;
			}
		}
		
		if (strcmp(section, "[Ground-Enemy]") == 0)
		{
			while (true)
			{
				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1)
				{
					break;
				}
				
				enemyArray[numEnemies] = new GroundEnemy();
				enemyArray[numEnemies]->x = x;
				enemyArray[numEnemies]->y = y;
				numEnemies++;
			}
		}
		


		if (strcmp(section, "[End]") == 0)
		{
			break;
		}
	}

	fclose(file);
}