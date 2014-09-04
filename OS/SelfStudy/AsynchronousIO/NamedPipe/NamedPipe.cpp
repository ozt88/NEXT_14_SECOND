// NamedPipe.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

#define BUF_SIZE 1024

int CommToClient( HANDLE );

int _tmain(int argc, _TCHAR* argv[])
{
	LPTSTR pipeName = _T( "\\\\.\\pipe\\simple_pipe" );
	HANDLE hPipe;
	while( 1 )
	{
		hPipe = CreateNamedPipe(
			pipeName ,
			PIPE_ACCESS_DUPLEX ,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT ,
			PIPE_UNLIMITED_INSTANCES ,
			BUF_SIZE ,
			BUF_SIZE ,
			20000 ,
			NULL );

		if( hPipe == INVALID_HANDLE_VALUE )
		{
			return -1;
		}

		BOOL isSuccess = 0;
		isSuccess = ConnectNamedPipe( hPipe , NULL ) ? TRUE : GetLastError() == ERROR_PIPE_CONNECTED;

		if( isSuccess ) CommToClient( hPipe );
		else CloseHandle( hPipe );
	}
	return 1;
}

int CommToClient( HANDLE hPipe )
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile( hPipe , fileName , MAX_PATH*sizeof( TCHAR ) , &fileNameSize , NULL );
	if( !isSuccess || fileNameSize == 0 )
	{
		return -1;
	}

	FILE* filePtr = _tfopen(fileName , _T( "r" ) );
	if( filePtr == NULL )
	{
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD byteRead = 0;

	while( !feof( filePtr ) )
	{
		byteRead = fread( dataBuf , 1 , BUF_SIZE , filePtr );

		WriteFile( hPipe , dataBuf , byteRead , &bytesWritten , NULL );

		if( byteRead != bytesWritten )
		{
			break;
		}
	}

	FlushFileBuffers( hPipe );
	DisconnectNamedPipe( hPipe );
	CloseHandle( hPipe );
	return 1;

}