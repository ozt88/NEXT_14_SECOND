// VertualAlloc.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
// 
// DWORD PAGE_SIZE = 4096;
// DWORD COMMIT_SIZE = 1024 * 100 * PAGE_SIZE;
// DWORD RESERVE_SIZE = 3 * COMMIT_SIZE;
// 
// 
// int _tmain(int argc, _TCHAR* argv[])
// {
// 	SYSTEM_INFO si;
// 	GetSystemInfo( &si );
// 	DWORD pageSize = si.dwPageSize;
// 	wprintf( L"PageSize :%d \n" , pageSize );
// 
// 	if( pageSize != PAGE_SIZE )
// 		return -1;
// 
// 	LPVOID baseAddr = VirtualAlloc( 
// 		NULL , RESERVE_SIZE , MEM_RESERVE , PAGE_NOACCESS 
// 		);
// 
// 	if( !baseAddr )
// 		return -1;
// 
// 	char* startAllocAddr = ( char* )baseAddr;
// 	while( true )
// 	{
// 		wprintf( L"Press Any Number to Commit >>" );
// 		int in = 0;
// 		scanf( "%d" , &in );
// 
// 		for( DWORD i = 0; i < COMMIT_SIZE; i += PAGE_SIZE )
// 		{
// 			LPVOID result = VirtualAlloc( startAllocAddr ,
// 										  PAGE_SIZE , MEM_COMMIT , PAGE_READWRITE );
// 			if( result )
// 			{
// 				strcpy( startAllocAddr , "Dummy~~~~~ String~~~~" );
// 				startAllocAddr += PAGE_SIZE;
// 			}
// 			else
// 			{
// 				wprintf( L"COMMIT FAIL!!\n" );
// 				break;
// 			}
// 		}
// 	}
// 
// 	VirtualFree( baseAddr , 0 , MEM_RELEASE );
// 	system( "pause" );
// 	return 0;
// }
// 


#define PAGE_SIZE 4096

int _tmain( int argc , _TCHAR* argv[] )
{
	HANDLE hHeap = HeapCreate( HEAP_NO_SERIALIZE , PAGE_SIZE * 10 , PAGE_SIZE * 100 );

	int* pArr = ( int* )HeapAlloc( hHeap , 0 , sizeof( int ) * 30 );

	for( int i = 0; i < 10; ++i )
		pArr[i] = ( i + 1 ) * 100;

	for( int i = 0; i < 30; ++i )
		_tprintf( _T( "%d \n" ) , pArr[i] );

	HeapFree( hHeap , 0 , pArr );

	HeapDestroy( hHeap );

	getchar();
	return 0;
}

