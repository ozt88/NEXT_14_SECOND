#include "Bullet.h"
#include "stdafx.h"

Bullet::Bullet()
{
	m_Velocity = DEFAULT_BULLET_SPEED;
	m_Body = IDB_BITMAP2;
	m_Type = TYPE_BULLET;
	m_Hp = 1;
}

Bullet::Bullet( double srcPosX , double srcPosY , int angle )
{
	m_PosX = srcPosX;
	m_PosY = srcPosY;

	m_Width = 10;
	m_Length = 10;

	m_Type = TYPE_BULLET;
	m_Hp = 1;

	m_Body = IDB_BITMAP2;
	m_Velocity = DEFAULT_BULLET_SPEED;

	m_VelocityX = m_Velocity * cos( angle*3.14/180 );
 	m_VelocityY = -m_Velocity * sin( angle*3.14/180 );
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_PosX += m_VelocityX;
	m_PosY += m_VelocityY;
}

bool Bullet::IsDestroy()
{
	return (IsOutOfScreen()||m_Hp <= 0);
}

