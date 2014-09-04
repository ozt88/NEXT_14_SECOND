// VirtualMemory.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

#define MAX_PAGE 10

int* nextPageAddr;
DWORD pageCnt = 0;
DWORD pageSize;
int PageFaultExceptionFilter( DWORD );

int _tmain(int argc, _TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;

	GetSystemInfo( &sSysInfo );
	pageSize = sSysInfo.dwPageSize/1000;

	baseAddr = VirtualAlloc(
		NULL , 
		MAX_PAGE* pageSize ,
		MEM_RESERVE ,
		PAGE_NOACCESS );

	if( !baseAddr )
	{
		_tprintf_s( _T( "VirtualAlloc reserve failed.\n" ) );
	}
	
	//baseAddr 배열 시작 주소
	lpPtr = ( int* )baseAddr;
	nextPageAddr = ( int* )baseAddr;

	for( int i = 0; i < ( MAX_PAGE * pageSize )/sizeof(int); ++i )
	{
		__try
		{
			lpPtr[i] = i;
		}
		__except( PageFaultExceptionFilter( GetExceptionCode() ))
		{
			ExitProcess( GetLastError() );
		}
	}

	for( int i = 0; i < ( MAX_PAGE * pageSize ) / sizeof( int ); ++i )
	{
		_tprintf_s( _T( "%d " ) , lpPtr[i] );
	}
	_tprintf_s( _T( "\n" ) );
	BOOL isSuccess = VirtualFree(
		baseAddr ,
		NULL ,
		MEM_RELEASE );

	if( isSuccess )
	{
		_tprintf_s( _T( "Release succeeded!\n" ) );
	}
	else
	{
		_tprintf_s( _T( "Release failed!\n" ) );
	}

	return 0;
}

int PageFaultExceptionFilter( DWORD exptCode )
{
	if( exptCode != EXCEPTION_ACCESS_VIOLATION )
	{
		_tprintf_s( _T("Exception code = %d \n") , exptCode );
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf_s( _T("Exception is a page fault\n") );

	if( pageCnt >= MAX_PAGE )
	{
		_tprintf_s( _T( "Exception: out of pages \n" ) );
		return EXCEPTION_EXECUTE_HANDLER;
	}

	LPVOID lpvResult = VirtualAlloc(
		( LPVOID )nextPageAddr ,
		pageSize ,
		MEM_COMMIT ,
		PAGE_READWRITE );

	if( !lpvResult )
	{
		_tprintf_s( _T( "VirtualAlloc Failed \n" ) );
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_tprintf_s( _T( "Allocating another page.\n" ) );
	}
	pageCnt++;
	nextPageAddr += pageSize / sizeof( int );

	return EXCEPTION_CONTINUE_EXECUTION;
}

