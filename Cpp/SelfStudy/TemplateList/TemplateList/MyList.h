#pragma once

template <typename T>
class MyList
{

public:

	MyList();
	~MyList();

public:
	struct Node;
	struct Iterator;
	
	size_t			Size(){ return m_Size;}
	bool			Empty() { return m_Size == 0; }
	void			Insert( Iterator& insertIter , T data);
	void			PushBack(T elem) { Insert( m_Tail , elem );}
	void			PopBack(){ Erase( m_Tail->prev ); }
	void			PushFront( T elem ){ Insert( m_Head->next , elem );}
	void			PopFront(){ Erase( m_Head->next ); }
	void			Clear();
	
	Iterator&		Begin()
	{
		m_Iterator.m_pNode = m_Head->next;
		return m_Iterator;
	}
	
	Iterator&		End()
	{
		m_Iterator.m_pNode = m_Tail;
		return m_Iterator;
	}

	Iterator&		RBegin()
	{
		m_Iterator.m_pNode = m_Tail->prev;
		return m_Iterator;
	}

	Iterator&		REnd()
	{
		m_Iterator.m_pNode = m_Head;
		return m_Iterator;
	}
	
	Iterator&		Erase( const Iterator& deleteIter )
	{
		Node* deleteNode = deleteIter.m_pNode;
		m_Iterator = deleteIter;
		++m_Iterator;
		Erase( deleteNode );
		return m_Iterator;
	}

	

private:
	void			Erase( Node* deleteNode );
	void			Insert( Node* nextNode , T data );

private:
	Iterator		m_Iterator;
	Node*			m_Head;
	Node* 			m_Tail;
	size_t			m_Size;
};

template <typename T>
void MyList<T>::Insert( Node* nextNode , T data )
{
	_ASSERT( nextNode != nullptr &&
			 nextNode != m_Head );
	Node* insertNode = new Node( data );
	Node* prevNode = nextNode->prev;
	insertNode->next = nextNode;
	insertNode->prev = prevNode;
	nextNode->prev = insertNode;
	prevNode->next = insertNode;
}



//LIST METHOD IMPLEMENTS


template <typename T>
MyList<T>::MyList()
	:m_Head(nullptr) , m_Tail(nullptr) , m_Size(0) , m_Iterator()
{
	m_Head = new Node();
	m_Tail = new Node();
	m_Head->next = m_Tail;
	m_Tail->prev = m_Head;
}

template <typename T>
MyList<T>::~MyList()
{
	Clear();
	delete m_Head;
	delete m_Tail;
}

template <typename T>
void MyList<T>::Clear()
{
	Node* deleteNode = nullptr;
	for( auto iter = Begin(); iter != End(); )
	{
		iter = Erase( iter );
	}
}

template <typename T>
void MyList<T>::Insert( Iterator& insertIter , T data )
{
	Node* nextNode = insertIter.m_pNode;
	insertIter.m_pNode = insertNode;
	Insert( nextNode , data );
	++m_Size;
}

template <typename T>
void MyList<T>::Erase( Node* deleteNode )
{
	_ASSERT( deleteNode != nullptr &&
			 deleteNode != m_Head  &&
			 deleteNode != m_Tail );
	
	Node* nextNode = deleteNode->next;
	Node* prevNode = deleteNode->prev;
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	delete deleteNode;
	deleteNode = nullptr;
	--m_Size;
}



//NODE STRUCT

template <typename T>
struct MyList<T>::Node
{
	Node()
		:data() , next( nullptr ) , prev( nullptr )
	{
	}
	Node( T _data )
		:data(_data) , next(nullptr) , prev(nullptr)
	{
	}
	T		data;
	Node*	next;
	Node*	prev;
};


//Iterator CLASS
template <typename T>
struct MyList<T>::Iterator
{
	Node* m_pNode;

	Iterator()
	{
		m_pNode = nullptr;
	}

	~Iterator()
	{
	}

	T& operator*( )
	{
		return m_pNode->data;
	}

	void operator=( Iterator that )
	{
		m_pNode = that.m_pNode;
	}

	void operator++( )
	{
		if( this->m_pNode == nullptr )
		{
			m_pNode = nullptr;
		}
		m_pNode = m_pNode->next;
	}

	void operator--( )
	{
		if( this->m_pNode == nullptr )
		{
			m_pNode = nullptr;
		}
		m_pNode = m_pNode->prev;
	}

	bool operator==( const Iterator& that )
	{
		return ( this->m_pNode == that.m_pNode );
	}

	bool operator!=( const Iterator& that )
	{
		return ( this->m_pNode != that.m_pNode );
	}

};
