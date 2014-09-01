#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
	:m_HandleNum( 0 )
{
	_tcscpy_s( m_DataName , _T( "PlayerData.dat" ) );
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	for( int i = 0; i < PLAYER_NUM; ++i )
	{
		m_PlayerList.push_back( new CPlayer( MAX_HP , i + 1001 , rand() % 100 , rand() % 2 ) );
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
	PlayerInfo pi[PLAYER_NUM];
	int i = 0;
	for( auto player : m_PlayerList )
	{
		pi[i].m_HP = player->GetHP();
		pi[i].m_ID = player->GetId();
		pi[i].m_isMale = player->GetIsMale();
		pi[i++].m_Stage = player->GetStage();
	}
	WriteFile( hFile , pi , sizeof( pi ) ,
			   &numOfByteWritten , NULL );

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
	PlayerInfo pi[PLAYER_NUM];
	ReadFile( hFile , pi , sizeof( pi ) ,
			  &numOfByteToRead , NULL );
	CloseHandle( hFile );
	Clear();
	int i = 0;
	for( auto player : pi )
	{
		m_PlayerList.push_back( new CPlayer( player.m_HP, player.m_ID , player.m_Stage , player.m_isMale ) );
	}
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

void GameManager::Attack( CPlayer* from , CPlayer* to )
{
	_tprintf_s( _T( "BEGIN : from #%d to #%d\n" ) , from->GetId() , to->GetId() );
	EnterCriticalSection( from->GetLock() );
	while( !TryEnterCriticalSection( to->GetLock() ) )
	{
		LeaveCriticalSection( from->GetLock() );
		EnterCriticalSection( from->GetLock() );
	};
	_tprintf_s( _T( "--from %d enter critical section\n" ) , from->GetId() );
	_tprintf_s( _T( "--from %d enter critical section\n" ) , to->GetId() );

	to->Attacked();
	from->Attacking();

	Sleep(100);

	LeaveCriticalSection( to->GetLock() );
	_tprintf_s( _T( "--%d leave critical section\n" ) , from->GetId() );
	LeaveCriticalSection( from->GetLock());
	_tprintf_s( _T( "--%d leave critical section\n" ) , from->GetId() );

}

unsigned int WINAPI GameManager::WrapedThreadProc( LPVOID lpparam )
{
	GameManager* gm = ( GameManager* )lpparam;
	return gm->ThreadProc();
}

void GameManager::Run()
{
	DWORD dwThreadId[PLAYER_NUM];
	HANDLE hThread[PLAYER_NUM];

	for( DWORD i = 0; i < PLAYER_NUM; ++i )
	{
		hThread[i] = ( HANDLE )_beginthreadex( NULL , NULL , 
											   WrapedThreadProc , 
											   (void*)this,
											   CREATE_SUSPENDED , 
											  ( unsigned int* )&dwThreadId[i] );
	}

	_tprintf_s( _T( "====================BEGIN=====================\n" ) );
	for( DWORD i = 0; i < PLAYER_NUM; ++i )
	{
		ResumeThread( hThread[i] );
	}

	WaitForMultipleObjects( PLAYER_NUM , hThread , TRUE , INFINITE );

	_tprintf_s( _T( "====================RESULT====================\n" ) );

	for(auto player : m_PlayerList )
	{
		player->print();
	}

	for( DWORD i = 0; i < PLAYER_NUM; ++i )
	{
		CloseHandle( hThread[i] );
	}

	getchar();
	return ;
}

DWORD GameManager::ThreadProc()
{
	srand( GetCurrentThreadId() );

	int from = m_HandleNum++;

	for( int i = 0; i < ATTACK_COUNT; ++i )
	{
		int to = 0;

		while( 1 )
		{
			to = rand() % PLAYER_NUM;
			if( from != to ) break;
		}
		Attack( m_PlayerList[from] , m_PlayerList[to] );
	}
	return 0;
}

void GameManager::Clear()
{
	for( auto player : m_PlayerList )
	{
		if( player != nullptr )
		{
		delete player;
		player = nullptr;
		}
	}
	m_PlayerList.clear();
}

