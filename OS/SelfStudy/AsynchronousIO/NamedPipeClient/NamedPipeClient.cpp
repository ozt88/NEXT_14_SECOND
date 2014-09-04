// NamedPipe.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

#define BUF_SIZE 1024


int _tmain( int argc , _TCHAR* argv[] )
{
	LPTSTR pipeName = _T( "\\\\.\\pipe\\simple_pipe" );
	TCHAR readDataBuf[BUF_SIZE + 1];
	HANDLE hPipe;

	while( 1 )
	{
		hPipe = CreateFile(
			pipeName ,
			GENERIC_READ|GENERIC_WRITE,
			NULL,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL);

		if( hPipe != INVALID_HANDLE_VALUE )
		{
			break;
		}

		if( GetLastError() != ERROR_PIPE_BUSY )
		{
			return 0;
		}
		if( !WaitNamedPipe( pipeName , 20000 ) )
		{
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL isSuccess = SetNamedPipeHandleState( hPipe , &pipeMode , NULL , NULL );
	if( !isSuccess )
		return 0;
	
	LPCTSTR fileName = _T( "news.txt" );
	DWORD bytesWritten = 0;
	isSuccess = WriteFile( hPipe , fileName , ( _tcslen( fileName ) + 1 )* sizeof( TCHAR ) , &bytesWritten , NULL );
	if( !isSuccess )
		return 0;

	DWORD bytesRead = 0;
	while( 1 )
	{
		isSuccess = ReadFile( hPipe , readDataBuf , BUF_SIZE * sizeof( TCHAR ) , &bytesRead , NULL );
		if( !isSuccess && GetLastError() != ERROR_MORE_DATA )
			break;

		readDataBuf[bytesRead] = 0;
		_tprintf_s( _T( "%s \n" ) , readDataBuf );
	}
	
	CloseHandle ( hPipe );
	getchar();
	return 1;
}
