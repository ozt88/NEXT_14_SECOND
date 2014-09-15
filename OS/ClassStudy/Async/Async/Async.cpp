// Async.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

void Practice1( TCHAR* fileName );
void Practice2();

void CALLBACK CompRoutine( DWORD errorCode , DWORD numOfByteTransefered , LPOVERLAPPED overlapped )
{
	_tprintf_s( _T( "ErrorCode = %u \n NumOfByteTransefered = %u \n" ) , errorCode , numOfByteTransefered );
	_tprintf_s( _T( "FileName = %s \n" ) , overlapped->hEvent );
}



int _tmain(int argc, _TCHAR* argv[])
{

	TCHAR* fileName = _T( "test1.txt" );
	size_t sizeofFile = 1024 * 1024 * 100;
	HANDLE hFile = CreateFile( fileName , GENERIC_WRITE ,
							   FILE_SHARE_WRITE ,
							   0 , CREATE_ALWAYS ,
							   FILE_FLAG_OVERLAPPED , 0 );

	TCHAR* writeFile = ( TCHAR* )malloc( sizeof( TCHAR ) * sizeofFile );
	OVERLAPPED overlapedInst;
	memset( &overlapedInst , 0 , sizeof( overlapedInst ) );
	overlapedInst.hEvent = ( HANDLE )fileName;

	WriteFileEx( hFile , writeFile ,
				 sizeofFile*sizeof( TCHAR ) ,
				 &overlapedInst , CompRoutine );

	for( int i = 0; i < 100; ++i )
	{
		_tprintf_s( _T( "Do something\n" ) );
	}
	SleepEx( INFINITE , TRUE );
	CloseHandle( hFile );

	getchar();
	return 0;
}

