// Operation2.cpp 
//���α׷� ���� : �ܼ� ��� ���α׷� 2.


#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SetPriorityClass( GetCurrentProcess() , HIGH_PRIORITY_CLASS );

	while( 1 )
	{
		for( DWORD i = 0; i < 10000; i++ )
		{
			for( DWORD j = 0; j < 10000; j++ )
			{
				//BUSY WAITING!!!
			}
		}
		_fputts( _T( "Operation2.exe\n" ) , stdout );
	}
	return 0;
}

