#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy( int posX , int posY )
{
	m_PosX = posX;
	m_PosY = posY;

	m_Width = 40;
	m_Length = 40;

	m_Type = TYPE_ENEMY;
	m_Hp = 1;

	m_Body = IDB_BITMAP3;
	m_VelocityX = 10;
	m_VelocityY = 0;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
// 	srand(time(NULL));
// 	int randomMove = rand() % 10;
//    	if( randomMove == 0 && !IsOutOfScreen())
// 	{
	m_PosX += m_VelocityX;
// 	}
// 	else if(randomMove == 1 && !IsOutOfScreen())
// 	{
// 		m_PosY -= m_VelocityY;
// 	}
}

bool Enemy::IsDestroy()
{
	return false;
}

