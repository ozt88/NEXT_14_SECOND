// Heap.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

typedef int ListElementDataType;

struct Node
{
	ListElementDataType data;
	struct Node* next;
};

Node* head;
Node* tail;

HANDLE hHeap;

void InitListHeap()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo( &sysInfo );
	UINT pageSize = sysInfo.dwPageSize;
	hHeap = HeapCreate(
		HEAP_NO_SERIALIZE , pageSize * 10 , pageSize * 100 );

}

void InitList( void )
{
	InitListHeap();
	head = ( Node* )HeapAlloc( hHeap , HEAP_NO_SERIALIZE , sizeof( Node ) );
	tail = ( Node* )HeapAlloc( hHeap , HEAP_NO_SERIALIZE , sizeof( Node ) );
	head->next = tail;
	tail->next = tail;
}

int DeleteNode( int data )
{
	Node* curNode = head;
	Node* nextNode = curNode->next;

	while( nextNode->data != data && nextNode != tail )
	{
		curNode = curNode->next;
		nextNode = curNode->next;
	}

	if( nextNode != tail )
	{
		curNode->next = nextNode->next;
		HeapFree( hHeap , NULL , nextNode );
		return 1;
	}
	return 0;
}


void OrderedInsert( int data )
{
	Node* curNode = head;
	Node* nextNode = curNode->next;
	Node* newNode = nullptr;
	while( nextNode->data <= data && nextNode != tail )
	{
		curNode = nextNode;
		nextNode = curNode->next;
	}

	newNode = ( Node* )HeapAlloc( hHeap , NULL , sizeof( Node ) );
	newNode->data = data;
	curNode->next = newNode;
	newNode->next = nextNode;
}

void PrintAllList()
{
	Node* curNode = head->next;
	while( curNode != tail )
	{
		_tprintf_s( _T( "%-4d" ) , curNode->data );
		curNode = curNode->next;
	}
	_tprintf_s( _T( "\n\n" ) );
}

void DeleteAll()
{
	HeapDestroy( hHeap );
	InitList();
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitList();
	OrderedInsert( 1 );
	OrderedInsert( 2 );
	OrderedInsert( 3 );
	PrintAllList();

	OrderedInsert( 4 );
	OrderedInsert( 5 );
	OrderedInsert( 6 );
	PrintAllList();

	DeleteNode( 2 );
	DeleteNode( 5 );
	PrintAllList();

	DeleteAll();


	OrderedInsert( 6 );
	OrderedInsert( 5 );
	OrderedInsert( 4 );
	PrintAllList();


	OrderedInsert( 3 );
	OrderedInsert( 2 );
	OrderedInsert( 1 );
	PrintAllList();

	DeleteAll();

	return 0;
}

