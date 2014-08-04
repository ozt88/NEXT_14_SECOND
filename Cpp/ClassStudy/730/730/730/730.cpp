// 730.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

int atoi( char* str )
{
	int length = 0;
	int result = 0;
	int digit = 1;

	while( *str != '\0' )
	{
		length++;
		str++;
	}

	
	while( length-- >= 0 )
	{
		int num = *(--str) - '0';
		if( num > -1 && num < 10 )
		{
			result += num*digit;
		}
		digit *= 10;
	}

	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* num = "199qwe";
	printf( "%d\n" , atoi( num ) );
	getchar();
	return 0;
}

