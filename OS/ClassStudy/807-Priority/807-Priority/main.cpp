#include "stdafx.h"

void Worker( _TCHAR* str )
{
	for( int i = 0; i < 100; ++i )
	{
		for( int j = 0; j < 100000; ++j )
		{
			//busy wating...
		}
		Sleep( 0 );
	}
	_tprintf_s( _T( "%s End \n" ) , str );
}

int _tmain( int argc , _TCHAR* argv[] )
{
	if( argc <= 1 )
	{
		return 0;
	}

	int priority = _wtoi( argv[1] ) % 3;

	switch( priority )
	{
		case 0:
			SetPriorityClass( GetCurrentProcess() , IDLE_PRIORITY_CLASS );
			Worker( _T( "IDLE" ));
			break;
		case 1:
			SetPriorityClass( GetCurrentProcess() , HIGH_PRIORITY_CLASS );
			Worker( _T( "HIGH" ) );
			break;
		case 2:
			SetPriorityClass( GetCurrentProcess() , REALTIME_PRIORITY_CLASS );
			Worker( _T( "REAL" ) );
			break; 
		default:
			break;
	}
	getchar();
	return 0;
}