#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
	_tcscpy_s( m_DataName , _T( "PlayerData.dat" ) );
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	
	for( int i = 0; i < 5; ++i )
	{
		m_PlayerList[i] = CPlayer( rand() % 100 , i , rand() % 100 , rand() % 2 );
	}
}

void GameManager::SaveData()
{
	HANDLE hFile = CreateFile( m_DataName , GENERIC_WRITE ,
							   FILE_SHARE_WRITE , NULL ,
							   CREATE_ALWAYS , 
							   FILE_ATTRIBUTE_NORMAL ,NULL
							   );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "FILE OPEN FAULT!\n" ) );
		return;
	}
	DWORD numOfByteWritten = 0;
	BOOL bWriteResult = true;
	bWriteResult = WriteFile( hFile , m_PlayerList , sizeof(m_PlayerList) ,
							  &numOfByteWritten , NULL
							  );

	CloseHandle( hFile );
	return;
}

void GameManager::LoadData()
{
	HANDLE hFile = CreateFile(
		m_DataName , GENERIC_READ ,
		FILE_SHARE_READ , NULL , OPEN_EXISTING ,
		FILE_ATTRIBUTE_NORMAL , NULL
		);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "FILE OPEN FAULT!\n" ) );
		return;
	}

	DWORD numOfByteToRead = 0;
	ReadFile( hFile , m_PlayerList , sizeof( m_PlayerList ) ,
			  &numOfByteToRead , NULL );
	CloseHandle( hFile );
	return;
}

void GameManager::FindAndPrint()
{
	int findId = 0;
	CPlayer findPlayer;
	_tprintf_s( _T( "Input Id >>" ) );
	std::cin >> findId;
	if( findId > PLAYER_NUM || findId < 0 )
	{
		_tprintf_s( _T( "Input Error!\n" ) );
		return;
	}

	HANDLE hFile = CreateFile(
		m_DataName , GENERIC_READ ,
		FILE_SHARE_READ , NULL , OPEN_EXISTING ,
		FILE_ATTRIBUTE_NORMAL , NULL
		);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "FILE OPEN FAULT!\n" ) );
		return;
	}
	DWORD numOfByteToRead = 0;
	SetFilePointer( hFile , findId*sizeof(CPlayer) , NULL , FILE_BEGIN );
	ReadFile( hFile , &findPlayer , sizeof( findPlayer ) , 
			  &numOfByteToRead , NULL );
	findPlayer.print();
	CloseHandle( hFile );
}
