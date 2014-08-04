#include "Tank.h"


Tank::Tank()
{
	m_Body = MAKEINTRESOURCE( IDB_BITMAP1 );
	m_Position.posX = 100;
	m_Position.posY = 100;
}


Tank::~Tank()
{
}


void Tank::Render(HWND& hWnd, HINSTANCE& hinst,
				   HDC& hdc, HDC& MemDC, PAINTSTRUCT& ps)
{
	HBITMAP myBitmap , OldBitmap;
	myBitmap = LoadBitmap( hinst , m_Body);
	OldBitmap = ( HBITMAP )SelectObject( MemDC , myBitmap );
	BitBlt( hdc , 0 + m_Position.posX , 0 + m_Position.posY , 
			123 + m_Position.posX , 160 + m_Position.posY ,
			MemDC , 0 , 0 , SRCCOPY );
	SelectObject( MemDC , OldBitmap );
	DeleteObject( myBitmap );
	DeleteDC( MemDC );
	EndPaint( hWnd , &ps );
}

void Tank::Move( Direction dir )
{
	switch (dir)
	{
		case UP:
			m_Position.posY -= BOX_SIZE;
			break;
		case DOWN:
			m_Position.posY += BOX_SIZE;
			break;
		case LEFT:
			m_Position.posX -= BOX_SIZE;
			break;
		case RIGHT:
			m_Position.posX += BOX_SIZE;
			break;
		default:
			break;
	}
}
