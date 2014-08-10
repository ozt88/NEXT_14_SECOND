// SuspendCount.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>

unsigned int WINAPI ThreadProc( LPVOID lpParam )
{
	while( 1 )
	{
		_tprintf_s( _T( "Running State! \n" ) );
		Sleep( 1000 );
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwThreadID;
	HANDLE hThread;
	DWORD susCnt;

	hThread = ( HANDLE )_beginthreadex( NULL , 0 ,
										ThreadProc ,
										NULL ,
										CREATE_SUSPENDED ,
										( unsigned* )&dwThreadID 
										);

	if( hThread == NULL )
	{
		_tprintf_s( _T( "Thread creation fault!\n" ) );
	}

	susCnt = ResumeThread( hThread );
	_tprintf_s( _T( "suspend count : %d \n" ) , susCnt );
	Sleep( 1000 );

	susCnt = SuspendThread( hThread );
	_tprintf_s( _T( "suspend count : %d \n" ) , susCnt );
	Sleep( 1000 );

	susCnt = SuspendThread( hThread );
	_tprintf_s( _T( "suspend count : %d \n" ) , susCnt );
	Sleep( 1000 );

	susCnt = ResumeThread( hThread );
	_tprintf_s( _T( "suspend count : %d \n" ) , susCnt );
	Sleep( 1000 );

	susCnt = ResumeThread( hThread );
	_tprintf_s( _T( "suspend count : %d \n" ) , susCnt );
	Sleep( 1000 );

	WaitForSingleObject( hThread , INFINITE );
	

	return 0;
}

