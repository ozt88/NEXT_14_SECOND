// mailSender.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain( int argc , _TCHAR* argv[] )
{
	HANDLE hMailSlot;
	TCHAR message[50];
	DWORD bytesWritten;


	hMailSlot = CreateFile( 
		SLOT_NAME , 
		GENERIC_WRITE , 
		FILE_SHARE_READ , 
		NULL , 
		OPEN_EXISTING , 
		FILE_ATTRIBUTE_NORMAL , 
		NULL );

	if( hMailSlot == INVALID_HANDLE_VALUE )
	{
		_fputts( _T( "Unable to create mailslot!\n" ) , stdout );
		return 1;
	}

	while( 1 )
	{
		_fputts( _T( "MY CMD>" ) , stdout );
		_fgetts( message , sizeof( message ) / sizeof( TCHAR ) , stdin );

		if( !WriteFile( hMailSlot , message , _tcslen( message )*sizeof( TCHAR ) , &bytesWritten , NULL ) )
		{
			_fputts( _T( "Unable to write!" ) , stdout );
			CloseHandle( hMailSlot );
			return 1;
		}
		if( !_tcsncmp( message , _T( "exit" ) , 4 ) )
		{
			_fputts( _T( "Good Bye!" ) , stdout );
			break;
		}
	}
	CloseHandle( hMailSlot );

	return 0;
}

