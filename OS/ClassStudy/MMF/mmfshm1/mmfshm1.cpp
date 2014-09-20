// mmfshm1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#define BUFFER_SIZE 1024

TCHAR* mmfObjName = _T( "Global//MyFileMapingObject" );
TCHAR* msg = _T( "This is the message coming from first process.\n" );

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hMapFile = CreateFileMapping( INVALID_HANDLE_VALUE , NULL , PAGE_READWRITE ,
										 0 , BUFFER_SIZE , mmfObjName );
	if( hMapFile == NULL )
	{
		return -1;
	}


	TCHAR* pWrite = ( TCHAR* )MapViewOfFile( hMapFile , FILE_MAP_ALL_ACCESS , 0 , 0 , BUFFER_SIZE );
	if( pWrite == NULL )
	{
		return -2;
	}

	memcpy( pWrite , msg , sizeof( TCHAR )* _tcslen( msg ) );
	
	getchar();
	UnmapViewOfFile( pWrite );
	CloseHandle( hMapFile );
	
	return 0;
}

