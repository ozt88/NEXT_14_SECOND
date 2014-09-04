// CompleteRoutine.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>


TCHAR strData1[] = _T( "North Korea gave foreign media access on Monday taslkdjlkq." );
TCHAR strData2[] = _T( "I'am Your Father Fucker." );
TCHAR strData3[] = _T( "You Fucking Jewish!." );


VOID WINAPI FileIOCompletionRoutine( DWORD , DWORD , LPOVERLAPPED );
OVERLAPPED overlappedFilePtr;

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR fileName[] = _T( "data.txt" );
	HANDLE hFile = CreateFile( fileName , GENERIC_WRITE , FILE_SHARE_WRITE , NULL , CREATE_ALWAYS , FILE_FLAG_OVERLAPPED , NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return -1;
	}

	OVERLAPPED overlappedInst1;
	memset( &overlappedInst1 , 0 , sizeof( overlappedInst1 ) );
	overlappedInst1.hEvent = ( HANDLE )_T("First IO");
	WriteFileEx( hFile , strData1 , sizeof( strData1 ) , &overlappedInst1 , FileIOCompletionRoutine );
	overlappedFilePtr.Offset += _tcslen( strData1 ) * sizeof( TCHAR );

	OVERLAPPED overlappedInst2;
	memset( &overlappedInst2 , 0 , sizeof( overlappedInst2 ) );
	overlappedInst2.Offset = overlappedFilePtr.Offset;
	overlappedInst2.hEvent = ( HANDLE )_T("Second IO");
	WriteFileEx( hFile , strData2 , sizeof( strData2 ) , &overlappedInst2 , FileIOCompletionRoutine );
	overlappedFilePtr.Offset += _tcslen( strData2 ) * sizeof( TCHAR );

	OVERLAPPED overlappedInst3;
	memset( &overlappedInst3 , 0 , sizeof( overlappedInst3 ) );
	overlappedInst3.Offset = overlappedFilePtr.Offset;
	overlappedInst3.hEvent = ( HANDLE )_T("Third IO");
	WriteFileEx( hFile , strData3 , sizeof( strData3 ) , &overlappedInst3 , FileIOCompletionRoutine );

	SleepEx( INFINITE , TRUE );
	CloseHandle( hFile );
	getchar();
	return 1;
}

VOID WINAPI FileIOCompletionRoutine( DWORD errorCode , DWORD numOfBytesTransfered , LPOVERLAPPED overlapped )
{
	_tprintf_s( _T( "**************FILE WRITE RESULT**************\n" ) );
	_tprintf_s( _T( "Error Code: %u\n" ), errorCode );
	_tprintf_s( _T( "Transfered bytes len: %u\n" ), numOfBytesTransfered );
	_tprintf_s( _T( "The Other info: %s\n" ), (TCHAR*)overlapped->hEvent );

}

