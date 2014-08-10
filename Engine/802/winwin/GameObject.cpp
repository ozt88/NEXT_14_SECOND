#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Render( const HWND& hWnd , const HINSTANCE& hinst ,
			 HDC hdc )
{
	HDC MemDC;
	HBITMAP myBitmap , OldBitmap;
	

	MemDC = CreateCompatibleDC( hdc );
	myBitmap = LoadBitmap( hinst , MAKEINTRESOURCE(m_Body) );
	OldBitmap = ( HBITMAP )SelectObject( MemDC , myBitmap );
	BitBlt( hdc , m_PosX, m_PosY ,
			m_Width , m_Length ,
			MemDC , 0 , 0 , SRCCOPY );
	SelectObject( MemDC , OldBitmap );
	DeleteObject( myBitmap );
	DeleteDC( MemDC );

}

bool GameObject::IsClashed( GameObject* otherObject )
{
	return ( m_PosX < otherObject->GetEndPosX() && GetEndPosX() > otherObject->GetPosX()
			 && m_PosY < otherObject->GetEndPosY() && GetEndPosY() > otherObject->GetPosY() );
}


