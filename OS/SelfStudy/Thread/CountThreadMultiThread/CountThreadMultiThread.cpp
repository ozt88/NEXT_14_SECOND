// Thread.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
			NULL ,								//����Ʈ ���� �Ӽ� ����
			0 ,									//����Ʈ ���û�����
			ThreadProc ,						//������ �Լ�
			( LPVOID )cntOfThread ,				//������ �Լ� ��������
			0 ,									//����Ʈ ���� flag ����
			(unsigned *)&dwThreadID[cntOfThread]//������ID ��ȯ
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

