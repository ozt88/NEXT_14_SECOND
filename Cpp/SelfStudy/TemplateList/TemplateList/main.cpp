// TemplateList.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MyList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	MyList <std::string> testList;

	testList.PushBack( "김연우" );
	testList.PushBack( "김유신" );
	testList.PushBack( "김건모" );
	testList.PushBack( "김갑환" );
	testList.PushBack( "김짱쌤" );

	printf_s( "TEST 1\n" );
	for( auto it = testList.Begin(); it != testList.End(); ++it)
	{
		printf_s( "%s\n" , (*it).c_str() );
	}

	testList.PushFront( "이순신" );
	testList.PushFront( "이고잉" );
	testList.PushFront( "이과인" );
	testList.PushFront( "이말년" );
	testList.PushFront( "이마트" );

	printf_s( "TEST 2\n" );
	for( auto it = testList.Begin(); it != testList.End(); ++it )
	{
		printf_s( "%s\n" , ( *it ).c_str() );
	}

	testList.PopBack(); 
	testList.PopBack(); 
	testList.PopFront(); 
	testList.PopFront(); 
	testList.PopFront();
	
	printf_s( "TEST 3\n" );
	for( auto it = testList.Begin(); it != testList.End(); ++it )
	{
		printf_s( "%s\n" , ( *it ).c_str() );
	}

	testList.Clear();
	printf_s( "TEST 4\n" );
	for( auto it = testList.Begin(); it != testList.End(); ++it )
	{
		printf_s( "%s\n" , ( *it ).c_str() );
	}
	return 0;
}

