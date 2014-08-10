#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	Enemy( int posX , int posY );
	~Enemy();
	void Update();
	bool IsDestroy();

private:
	int m_VelocityX;
	int m_VelocityY;
};

