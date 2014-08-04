#pragma once
#include "stdafx.h"

#define BOX_SIZE 30

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Pos
{
	int posX;
	int posY;
};

class Tank
{
public:
	Tank();
	~Tank();
	
	int getPosX()
	{
		return m_Position.posX;
	}
	
	int getPosY()
	{
		return m_Position.posY;
	}

	//void Render( HWND& hWnd , HINSTANCE& g_hinst , HDC& hdc , HDC& MemDC , PAINTSTRUCT& ps , RECT& rt );
	void Render( HWND& hWnd , HINSTANCE& hinst, HDC& hdc , HDC& MemDC , PAINTSTRUCT& ps );
	void Move( Direction dir );
private:
	Pos m_Position;
	LPWSTR m_Body; 
};

