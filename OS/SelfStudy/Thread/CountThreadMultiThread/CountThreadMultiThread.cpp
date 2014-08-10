// Thread.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>

#define MAX_THREADS (1024 * 10)

unsigned int WINAPI ThreadProc( LPVOID lpParam )
{
	DWORD threadNum = ( DWORD )lpParam;
	while( 1 )
	{
		_tprintf_s( _T( "thread num : %d \n" ) , threadNum );
		Sleep( 1000 );
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain( int argc , _TCHAR* argv[] )
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	while( 1 )
	{
		hThread[cntOfThread] =
			(HANDLE) _beginthreadex(
			NULL ,								//디폴트 보안 속성 지정
			0 ,									//디폴트 스택사이즈
			ThreadProc ,						//쓰레드 함수
			( LPVOID )cntOfThread ,				//쓰레드 함수 전달인자
			0 ,									//디폴트 생성 flag 지정
			(unsigned *)&dwThreadID[cntOfThread]//쓰레드ID 반환
			);

		if( hThread[cntOfThread] == NULL )
		{
			_tprintf_s(
				_T( "MAXIMUM THREAD NUMBER: %d \n" ) ,
				cntOfThread
				);
			break;
		}
		cntOfThread++;
	}
	for( DWORD i = 0; i < cntOfThread; i++ )
	{
		CloseHandle( hThread[i] );
	}

	return 0;
}

