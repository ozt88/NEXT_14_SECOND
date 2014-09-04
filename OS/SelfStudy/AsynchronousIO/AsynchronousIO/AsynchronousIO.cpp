// AsynchronousIO.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include <windows.h>

#define BUF_SIZE 1024

int CommToClient( HANDLE );

int _tmain( int argc , _TCHAR* argv[] )
{
	LPTSTR pipeName = _T( "\\\\.\\pipe\\simple_pipe" );
	HANDLE hPipe;
	while( 1 )
	{
		hPipe = CreateNamedPipe(
			pipeName ,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED ,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT ,
			PIPE_UNLIMITED_INSTANCES ,
			BUF_SIZE / 2 ,
			BUF_SIZE / 2 ,
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
	FILE* filePtr;
	_tfopen_s( &filePtr , fileName , _T( "r" ) );
	if( filePtr == NULL )
	{
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset( &overlappedInst , 0 , sizeof( overlappedInst ) );
	overlappedInst.hEvent = CreateEvent(
		NULL , //보안설정
		TRUE , //manual 리셋 이벤트
		TRUE , //초기 상태 = non-signaled 
		NULL   //unnamed event object
		);

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;
	DWORD bytesTransfer = 0; 

	while( !feof( filePtr ) )
	{
		bytesRead = fread( dataBuf , 1 , BUF_SIZE , filePtr );
		bytesWrite = bytesRead;

		isSuccess = WriteFile( hPipe , dataBuf , bytesWrite , &bytesWritten , &overlappedInst );
		if( !isSuccess && GetLastError() != ERROR_IO_PENDING)
		{
			break;
		}

		//여기에 입력을 하면 다른 작업을 할 수 있다!

		WaitForSingleObject( overlappedInst.hEvent , INFINITE );
		GetOverlappedResult( hPipe , &overlappedInst , &bytesTransfer , FALSE );
		_tprintf_s( _T( "Transferred data size = %u \n" ) , bytesTransfer );
	}

	FlushFileBuffers( hPipe );
	DisconnectNamedPipe( hPipe );
	CloseHandle( hPipe );
	return 1;

}