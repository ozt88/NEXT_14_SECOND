// ThreadAdd.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

static int total = 0;

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
	DWORD* nPtr = ( DWORD* )lpParam;
	DWORD numOne = *nPtr;
	DWORD numTwo = *( nPtr + 1 );

	for( DWORD i = numOne; i <= numTwo; i++ )
	{
		total += i;
	}

	return total;
}

int _tmain( int argc , _TCHAR* argv[] )
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];
	DWORD paramThread[] = { 1 , 3 , 4 , 7 , 8 , 10 };

	for( int i = 0; i < 3; i++ )
	{
		hThread[i] =
			CreateThread(
			NULL , 0 ,
			ThreadProc ,
			( LPVOID )( &paramThread[2 * i] ) ,
			0 , &dwThreadID[i]
			);
	}

	if( hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL )
	{
		_tprintf_s( _T( "Thread Creation Fault! \n" ) );
		return -1;
	}

	WaitForMultipleObjects(
		3 ,
		hThread ,
		TRUE ,
		INFINITE
		);


	_tprintf_s( _T( "total (1~10): %d \n" ) , total );

	return 0;
}

