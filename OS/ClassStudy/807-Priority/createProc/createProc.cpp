// createProc.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define MAX_CHILD 12


int _tmain(int argc, _TCHAR* argv[])
{

	STARTUPINFO si[MAX_CHILD];
	PROCESS_INFORMATION pi[MAX_CHILD];
	HANDLE handles[MAX_CHILD];

	ZeroMemory( &si , sizeof( si ) );
	ZeroMemory( &pi , sizeof( pi ) );

	_TCHAR command[128];

	for( int i = 0; i < MAX_CHILD; ++i )
	{
		si[i].cb = sizeof( si[i] );
		memset( command , NULL , sizeof( command ) );
		_stprintf_s( command , _T( "Priority.exe %d\n" ) , i );

		if( !CreateProcess( NULL , command , NULL , NULL , FALSE , NULL , NULL , NULL , &si[i] , &pi[i] ) )
		{
			_tprintf_s( _T( "CreateProcess Failed (%d) \n") , GetLastError() );
			return 0;
		}

		handles[i] = pi[i].hProcess;
	}

	WaitForMultipleObjects( MAX_CHILD , handles, TRUE, INFINITE );

	for( int i = 0; i < MAX_CHILD; ++i )
	{
		CloseHandle( pi[i].hProcess );
		CloseHandle( pi[i].hThread );
	}

	return 0;
}

