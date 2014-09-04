// Event.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction( LPVOID lpParam );
unsigned int WINAPI CountThreadFunction( LPVOID lpParam );

typedef struct _SynchString
{
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
}SynchString;

SynchString gSynString;

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	gSynString.hEvent = CreateEvent( NULL , TRUE , FALSE , NULL );
	gSynString.hMutex = CreateMutex( NULL , FALSE , NULL );

	if( !gSynString.hEvent || !gSynString.hMutex)
	{
		return -1;
	}

	hThread[0] = ( HANDLE )_beginthreadex(
		NULL , 0 ,
		OutputThreadFunction ,
		NULL , 0 ,
		( unsigned* )&dwThreadID[0]
		);

	hThread[1] = ( HANDLE )_beginthreadex(
		NULL , 0 ,
		CountThreadFunction ,
		NULL , 0 ,
		( unsigned* )&dwThreadID[1]
		);

	if( !hThread[0] || !hThread[1] )
	{
		return -1;
	}

	_fputts( _T( "Insert string: " ) , stdout);
	_fgetts( gSynString.string , 30 , stdin );

	SetEvent( gSynString.hEvent );

	WaitForMultipleObjects( 2, hThread , TRUE, INFINITE );

	CloseHandle( gSynString.hEvent );
	CloseHandle( gSynString.hMutex );
	CloseHandle( hThread[0] );
	CloseHandle( hThread[1] );

	getchar();
	return 0;
}

unsigned int WINAPI OutputThreadFunction( LPVOID lpParam )
{
	WaitForSingleObject( gSynString.hEvent , INFINITE);
	//WaitForSingleObject( gSynString.hMutex , INFINITE );

	for( int i = 0; i < 10000; ++i )
	{
		for( int k = 0; k < 10000; ++k )
		{
		}
	}
	_fputts( _T( "OUTPUT STRING: " ) , stdout );
	_fputts( gSynString.string , stdout );
	SetEvent(gSynString.hEvent);
	//ReleaseMutex( gSynString.hMutex );
	return 0;
}

unsigned int WINAPI CountThreadFunction( LPVOID lpParam )
{
	WaitForSingleObject( gSynString.hEvent , INFINITE );
	WaitForSingleObject( gSynString.hMutex , INFINITE );

	for( int i = 0; i < 10000; ++i )
	{
		for( int k = 0; k < 10000; ++k )
		{
		}
	}
	_tprintf_s( _T( "output string length: %d \n" ) , 
				_tcslen( gSynString.string ) - 1 );
	ReleaseMutex( gSynString.hMutex );

	return 0;
}
