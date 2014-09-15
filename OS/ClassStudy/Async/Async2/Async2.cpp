// Async2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

int gcount = 0;

VOID CALLBACK timerProc(LPVOID, DWORD, DWORD)
{
	_tprintf_s( _T("%d: On Timer\n") , gcount++ );
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -10000000;

	hTimer = CreateWaitableTimer( NULL , FALSE , _T( "Waitable Timer" ) );

	SetWaitableTimer( hTimer , &liDueTime , 100 , timerProc , NULL , FALSE );

	
	for( int i = 0; i < 100; ++i )
	{
		SleepEx( INFINITE , TRUE );
		_tprintf_s( _T("%d: Outside Timer\n"), gcount++ );
	}
	CloseHandle( hTimer );
	return 0;
}

