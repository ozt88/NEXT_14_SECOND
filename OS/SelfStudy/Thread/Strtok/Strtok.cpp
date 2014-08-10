// Strtok.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

