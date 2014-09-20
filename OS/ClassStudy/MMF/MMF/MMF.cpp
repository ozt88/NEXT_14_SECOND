// MMF.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#define MAX_MAP_SIZE 1024 * 20

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFile = CreateFile( _T( "mmftest.txt" ) , GENERIC_READ | GENERIC_WRITE ,
							   0 , NULL , CREATE_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return -1;
	}
	 
	HANDLE hMapFile = CreateFileMapping( hFile , NULL , PAGE_READWRITE , 
										 0 , MAX_MAP_SIZE , NULL );
	if( hMapFile == INVALID_HANDLE_VALUE )
	{
		return -2;
	}
	char* pWrite = ( char* )MapViewOfFile( hMapFile , FILE_MAP_ALL_ACCESS , 
										   0 , 0 , 0 );
	if( pWrite == NULL )
	{
		return -3;
	}

	strcpy( pWrite , "sksmsrladusdndiqwelkjqwlekjlk............ MMF......TEST......" );
	char baseChar = 'A';
	for( int i = 0; i < 26; i += 3 )
	{
		pWrite[i] = baseChar++;
	}

	FlushViewOfFile( pWrite , NULL );

	CloseHandle( hMapFile );
	CloseHandle( hFile );
	getchar();

	return 0;
}

