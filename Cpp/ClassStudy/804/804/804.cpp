// 804.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>

void print( const std::string& str )
{
	printf_s( "%s" , str.c_str() );
}

int _tmain(int argc, _TCHAR* argv[])
{
	print( "I am a boqiweqwlkejqwlkj asldkjlkajslkdjaksjd" );
	getchar();
	return 0;
}

