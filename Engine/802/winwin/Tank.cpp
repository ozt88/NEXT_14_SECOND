#include "Tank.h"
#include "Bullet.h"

Tank::Tank()
{
	m_Hp = 50;
	m_PosX = 100;
	m_PosY = 100;
	m_Width = BOX_SIZE;
	m_Length = BOX_SIZE;
	m_VelocityX = 50;
	m_VelocityY = 50;
	m_Body = IDB_BITMAP1;
	m_Type = TYPE_TANK;
}


Tank::~Tank()
{
}

void Tank::Update()
{
}

Bullet* Tank::Attack( double angle )
{
	Bullet* newBullet = new Bullet( (m_PosX + GetEndPosX())/2 , m_PosY , angle );
	return newBullet;
}

void Tank::Move( int dir )
{
	switch( dir )
	{
		case 0:
			if( m_PosX > 0 ) m_PosX -= m_VelocityX;
			break;
		case 1:
			if( GetEndPosX() < 900 ) m_PosX += m_VelocityX;
			break;
		case 2:
			if( m_PosY > 0 ) m_PosY -= m_VelocityY;
			break;
		case 3: 
			if( GetEndPosY() < 450 ) m_PosY += m_VelocityY;
			break;
		default:
			break;
	}
}

bool Tank::IsDestroy()
{
	return m_Hp <= 0;
}
