// MMF.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>

void SortIntData( int* pSortArr , int num );

int _tmain(int argc, _TCHAR* argv[])
{
	//1.���� �ڵ� ����
	
	HANDLE hFile =
		CreateFile(
		_T( "data.dat" ) , GENERIC_READ | GENERIC_WRITE , 0 , NULL ,
		OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	if( hFile == INVALID_HANDLE_VALUE )
		_tprintf_s( _T( "Could not open file.\n" ) );
	


	//2.���� ������Ʈ ����

	HANDLE hMapFile =
		CreateFileMapping( 
		hFile , NULL , PAGE_WRITECOPY , 
		0 ,	1024 * 10 ,	NULL );				//���� ���� �ִ� �޸� ũ��
	if( !hMapFile )
		_tprintf_s( _T( "Could not create map of file.\n" ) );


	//3.�޸𸮿� ����

	int* pWrite =
		( int* )MapViewOfFile( hMapFile , FILE_MAP_COPY , 0 , 0 , 0 );
	if( !pWrite )
		_tprintf_s( _T( "Could not map view of file!\n" ) );

	//4.Do Something

	pWrite[0] = 1 , pWrite[1] = 3 , pWrite[2] = 0;
	pWrite[3] = 2 , pWrite[4] = 4 , pWrite[5] = 5;
	pWrite[6] = 8 , pWrite[7] = 6 , pWrite[8] = 7;

	//SortIntData( pWrite , 9 );
	for( int i = 0; i < 9; ++i )
	{
		_tprintf_s( _T( "%3d" ) , pWrite[i] );
	}
	_tprintf_s( _T( "\n" ) );
	UnmapViewOfFile( pWrite );
	CloseHandle( hMapFile );

	CloseHandle( hFile );
	_tprintf_s( _T( "End of process!\n" ) );
	return 0;
}

void SortIntData( int* pSortArr , int num )
{
	int temp;

	for( int i = 0; i < num - 1; ++i )
	{
		for( int j = 0; j < num; j++ )
		{
			if( pSortArr[j - 1] > pSortArr[j] )
			{
				temp = pSortArr[j - 1];
				pSortArr[j - 1] = pSortArr[j];
				pSortArr[j] = temp;
			}
		}
	}
}

