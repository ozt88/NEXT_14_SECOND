// OperationStateParent.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = { 0 , };
	PROCESS_INFORMATION pi;
	DWORD state;

	si.cb = sizeof( si );
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.lpTitle = _T( "return & exit" );

	TCHAR command[] = _T( "OperationStateChild.exe" );

	CreateProcess( NULL , command , NULL , NULL , TRUE ,
				   0 , NULL , NULL , &si , &pi );

// 	for( DWORD i = 0; i < 10000; i++ )
// 	{
// 		for( DWORD j = 0; j < 10000; j++ )
// 		{
// 			//Busy Waiting...
// 		}
// 	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	GetExitCodeProcess( pi.hProcess , &state);

	if( state == STILL_ACTIVE )
	{
		_tprintf_s( _T( "STILL_ACTIVE \n\n" ) );
	}
	else
	{
		_tprintf_s( _T( "state: %d \n\n" ) , state );
	}
	
	//CloseHandle( pi.hProcess );
	return 0;
}

