#pragma once
#include "stdafx.h"
#include "GameObject.h"

#define DEFAULT_BULLET_SPEED 20

class Bullet
	:public GameObject
{
public:
	Bullet();
	Bullet( double srcPosX , double srcPosY , int angle);
	void Update();
	~Bullet();
	bool IsDestroy();

private:
	int m_Velocity;
	int m_VelocityX;
	int m_VelocityY;
};

