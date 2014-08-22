// MyungDongGyoja.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <time.h>
#include <windows.h>
#include <process.h>

#define NUM_OF_CUSTOMER 50
#define NUM_OF_TABLE 10
#define MAX_TIME 30
#define MIN_TIME 10

DWORD eatingTime[NUM_OF_CUSTOMER];
clock_t startTime;
clock_t endTime;
HANDLE hSemaphore;
HANDLE hMutex;




void Open()
{
	WaitForSingleObject( hMutex , INFINITE );
	static int token = 0;
	if( token == 0 )
	{
		startTime = clock();
	}
	else
	{
		token++;
	}
	ReleaseMutex( hMutex );
}

void Close()
{
	WaitForSingleObject( hMutex , INFINITE );
	static int token2 = 0;
	if( ++token2 == NUM_OF_CUSTOMER )
	{
		endTime = clock();
	}
	ReleaseMutex( hMutex );
}

void GetCustomer( DWORD timeForEat )
{
	WaitForSingleObject( hSemaphore , INFINITE );
	Open();
	Sleep( timeForEat );
	Close();
	ReleaseSemaphore( hSemaphore , 1, NULL);
}


unsigned int WINAPI ThreadProc( LPVOID lwParam )
{
	GetCustomer( (DWORD) lwParam );
	return 0;
}

int _tmain( DWORD argc , TCHAR** argv )
{
	srand( ( unsigned )time( NULL ) );
	DWORD dwThreadId[NUM_OF_CUSTOMER];
	HANDLE hThread[NUM_OF_CUSTOMER];

	//동기화 생성
	hSemaphore = CreateSemaphore( 
		NULL , NUM_OF_TABLE , 
		NUM_OF_TABLE , NULL );
	hMutex = CreateMutex( NULL , FALSE , NULL );

	for( DWORD i = 0; i < NUM_OF_CUSTOMER; ++i )
	{
		eatingTime[i] = 
			(DWORD)
			(( ( double )rand() / ( double )RAND_MAX ) * MAX_TIME + MIN_TIME);
	}

	for( DWORD i = 0; i < NUM_OF_CUSTOMER; ++i )
	{
		hThread[i] = ( HANDLE )
			_beginthreadex
			(	
				NULL , 0 ,
				ThreadProc ,
				( void*) eatingTime[i] ,
				CREATE_SUSPENDED ,
				( unsigned* )&dwThreadId[i]
			);

		if( hThread[i] == NULL )
		{
			_tprintf_s( _T( "Thread Creation fault!\n" ) );
			return -1;
		}
	}



	for( DWORD i = 0; i < NUM_OF_CUSTOMER; ++i )
	{
		ResumeThread( hThread[i] );
	}
	WaitForMultipleObjects( NUM_OF_CUSTOMER , hThread , TRUE , INFINITE );


	//PRINT RESULT;
	printf( "Total time = %g\n" , (double)(endTime - startTime)*1000/(CLOCKS_PER_SEC) );

	for( DWORD i = 0; i < NUM_OF_CUSTOMER; ++i )
	{
		CloseHandle( hThread[i] );
	}

	CloseHandle( hSemaphore );
	CloseHandle( hMutex );
	return 0;
}


