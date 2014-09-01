#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_HP(0) , m_ID(0) , m_Stage(0) , m_isMale(TRUE) 
{
	m_Lock = new CRITICAL_SECTION();
	InitializeCriticalSection( m_Lock );
}

CPlayer::CPlayer( int _hp , int _id , int _stage , bool _isMale )
	: m_HP( _hp ) , m_ID( _id ) , m_Stage( _stage ) , m_isMale( _isMale )
{
	m_Lock = new CRITICAL_SECTION();
	InitializeCriticalSection( m_Lock );
}


CPlayer::~CPlayer()
{
	DeleteCriticalSection( m_Lock );
	if( m_Lock != nullptr )
	{
		delete m_Lock;
	}
}

void CPlayer::print()
{
	_tprintf_s( _T( "Player ID: %d, HP: %d, STAGE: %d, Gender: %s \n" ) ,
				m_ID , m_HP , m_Stage , 
				m_isMale ? _T( "MALE" ) : _T( "FEMALE" ) );

}
