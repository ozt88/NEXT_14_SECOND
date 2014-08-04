// ProcessSnapshot.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <TlHelp32.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
		return 0;
																														 
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	if( !Process32First( hProcessSnap , &pe32 ) )
	{
		_tprintf( _T( "Process32First ERROR\n" ) );
		CloseHandle( hProcessSnap );
		return 0;
	}

	do 
	{
		_tprintf( _T( "%d: %s\n" ) , pe32.th32ProcessID , pe32.szExeFile );
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle( hProcessSnap );

	return 0;
}

