// mmfshm1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#define BUFFER_SIZE 1024
TCHAR* mmfObjName = _T( "Global//MyFileMapingObject" );

int _tmain( int argc , _TCHAR* argv[] )
{
	HANDLE hMapFile = OpenFileMapping(  FILE_MAP_ALL_ACCESS ,
										false , mmfObjName );
	TCHAR* pWrite = ( TCHAR* )MapViewOfFile( hMapFile , FILE_MAP_ALL_ACCESS , 0 , 0 , BUFFER_SIZE );

	_tprintf_s( _T("%s"), pWrite );
	
	UnmapViewOfFile( pWrite );
	CloseHandle( hMapFile );
	getchar();
	return 0;
}

