// Strtok.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR string[] = _T( "Hey, get a life!" )
		_T( "You don't even have two pennies to rub together." );
	TCHAR seps[] = _T( " ,.!" );
	TCHAR* buffer = nullptr;
	TCHAR* token = _tcstok_s( string , seps , &buffer );

	while( token != NULL )
	{
		_tprintf_s( _T( "%s \n" ) , token );
		token = _tcstok_s( NULL , seps , &buffer );
	}

	return 0;
}

