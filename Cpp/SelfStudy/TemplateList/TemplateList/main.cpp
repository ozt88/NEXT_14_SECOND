// TemplateList.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "MyList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	MyList <std::string> testList;

	testList.PushBack( "�迬��" );
	testList.PushBack( "������" );
	testList.PushBack( "��Ǹ�" );
	testList.PushBack( "�谩ȯ" );
	testList.PushBack( "��¯��" );

	printf_s( "TEST 1\n" );
	for( auto it = testList.Begin(); it != testList.End(); ++it)
	{
		printf_s( "%s\n" , (*it).c_str() );
	}

	testList.PushFront( "�̼���" );
	testList.PushFront( "�̰���" );
	testList.PushFront( "�̰���" );
	testList.PushFront( "�̸���" );
	testList.PushFront( "�̸�Ʈ" );

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

