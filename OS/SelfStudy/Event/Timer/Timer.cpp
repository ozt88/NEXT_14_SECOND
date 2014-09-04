// Timer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#define _WIN32_WINNT 0x0400

#include "stdafx.h"
#include <windows.h>



int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTimer;
	liDueTimer.QuadPart = -10000000;

	hTimer = CreateWaitableTimer( NULL , FALSE , _T( "Waitable Timer" ) );
	if( !hTimer ) return -1;
	_tprintf_s(_T( "Waiting For 10 Sec\n" ));

	SetWaitableTimer( hTimer , &liDueTimer , 5000 , NULL , NULL , FALSE );
	
	for( int i = 0; i < 3; ++i)
	{
		WaitForSingleObject( hTimer , INFINITE );
		_tprintf_s( _T( "Timer was signaled.\n" ) );
		MessageBeep( MB_ICONEXCLAMATION );
	}

	CloseHandle( hTimer );
	getchar();
	return 0;
}

