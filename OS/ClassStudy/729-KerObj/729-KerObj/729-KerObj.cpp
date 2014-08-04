// 729-KerObj.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = { 0 , };
	PROCESS_INFORMATION pi;
	si.cb = sizeof( si );

	ZeroMemory( &pi , sizeof( pi ) );

	TCHAR command[] = _T( "calc.exe" );
	//SetCurrentDirectory( _T( "C:\\windows\\system32" ) );

	if( !CreateProcess( NULL , command , NULL , NULL , FALSE , NULL , NULL , NULL , &si , &pi ) )
	{
		_tprintf_s( _T( "CreateProcess Failed (%d). \n" ) , GetLastError() );
		return -1;
	}
	
	WaitForSingleObject( pi.hProcess , INFINITE );

	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	
	getchar();
	return 0;
}

