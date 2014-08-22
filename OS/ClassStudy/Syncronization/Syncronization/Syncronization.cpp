// Syncronization.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define NUM_OF_GATE 6

LONG gTotalCount = 0;
HANDLE hMutex;

void increase()
{
	WaitForSingleObject( hMutex , INFINITE );
	++gTotalCount;
	ReleaseMutex( hMutex );
}

unsigned int WINAPI ThreadProc( LPVOID lwParam )
{
	for( DWORD i = 0; i < 1000; i++ )
	{
		increase();
	}
	return 0;
}

int _tmain( DWORD argc , TCHAR** argv )
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];
	hMutex = CreateMutex(NULL , FALSE , NULL );
	
	for( DWORD i = 0; i < NUM_OF_GATE; ++i )
	{
		hThread[i] = (HANDLE)
			_beginthreadex( NULL , 0 ,
							ThreadProc ,
							NULL ,
							CREATE_SUSPENDED ,
							( unsigned* )&dwThreadId[i]
						   );
		if( hThread[i] == NULL )
		{
			_tprintf_s( _T( "Thread Creation fault!\n" ) );
			return -1;
		}
	}

	for( DWORD i = 0; i < NUM_OF_GATE; ++i )
	{
		ResumeThread( hThread[i] );
	}
	WaitForMultipleObjects( NUM_OF_GATE , hThread , TRUE , INFINITE );
	
	_tprintf_s( _T( "Total Count = %d \n" ) , gTotalCount );
	
	for( DWORD i = 0; i < NUM_OF_GATE; ++i )
	{
		CloseHandle( hThread[i] );
	}

	CloseHandle( hMutex );

	return 0;
}