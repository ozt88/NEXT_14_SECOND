
// Operation1.cpp
// ���α׷� ���� : �ܼ� ��� ���α׷�1.


#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = { 0 , };
	PROCESS_INFORMATION pi;
	si.cb = sizeof( si );
	TCHAR command[] = _T( "Operation2.exe" );

	CreateProcess( NULL , command , NULL , NULL , TRUE ,
				   0 , NULL , NULL , &si , &pi );

	while( 1 )
	{
		for( DWORD i = 0; i < 10000; i++ )
		{
			for( DWORD j = 0; j < 10000; j++ )
			{
				//Busy wating!!
			}
		}
		_fputts( _T( "Operation1.exe \n" ) , stdout );
	}
	return 0;
}

