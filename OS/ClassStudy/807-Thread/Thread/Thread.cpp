// Thread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define MAX_THREAD 10

DWORD_PTR Affinity_Mask = 0x0008; 

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
	if( 0 == SetThreadAffinityMask( GetCurrentThread() , Affinity_Mask ) )
	{
		_tprintf_s( _T( "Affinity fail %d\n" ) , GetLastError() );
	}

	SetThreadPriority( GetCurrentThread() , *( ( int* )lpParam ) );

	for( int i = 0; i < 100; ++i )
	{
		for( int j = 0; j < 10000000; ++j )
		{
			//busy
		}
		Sleep( 0 );
	}

	_tprintf( _T( "Thread Priority %d End \n" ) , *( ( int* )lpParam ) );
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwThreadId[MAX_THREAD] = { 0 , };
	HANDLE hThread[MAX_THREAD] = { NULL , };

	int threadPriority[MAX_THREAD] = { 0 , };

	for( int i = 0; i < MAX_THREAD; ++i )
	{
		switch( i % 5 )
		{
			case 0:
				threadPriority[i] = THREAD_PRIORITY_IDLE;
				break;
			case 1:
				threadPriority[i] = THREAD_PRIORITY_LOWEST;
				break;
			case 2:
				threadPriority[i] = THREAD_PRIORITY_NORMAL;
				break;
			case 3:
				threadPriority[i] = THREAD_PRIORITY_HIGHEST;
				break;
			case 4:
				threadPriority[i] = THREAD_PRIORITY_TIME_CRITICAL;
				break;
			default:
				break;
		}
	}

	for( int i = 0; i < MAX_THREAD; ++i )
	{
		hThread[i] = CreateThread( NULL , 0 , ThreadProc , ( LPVOID )&threadPriority[i] , 0 , &dwThreadId[i] );

		if( hThread[i] == NULL )
		{
			return -1;
		}
	}

	WaitForMultipleObjects( MAX_THREAD , hThread , TRUE , INFINITE );

	for( int i = 0; i < MAX_THREAD; ++i )
	{
		CloseHandle( hThread[i] );
	}

	getchar();
	return 0;
}

