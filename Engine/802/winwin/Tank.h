#pragma once
#include "stdafx.h"
#include "GameObject.h"

#define MAX_HP 50
#define INIT_POSX 100
#define INIT_POSY 100


class Bullet;

class Tank :public GameObject
{
public:
	Tank();
	~Tank();
	
	void Move(int Dir);
	void Update();
	Bullet* Attack( double angle );
	void Input( WPARAM wParam );
	int GetEndPosX()
	{
		return m_PosX + BOX_SIZE;
	}
	int GetEndPosY()
	{
		return m_PosY + BOX_SIZE;
	}
	bool IsDestroy();

private:

	int m_VelocityX;
	int m_VelocityY;

};

