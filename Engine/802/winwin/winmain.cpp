#include "stdafx.h"
#include "Tank.h"

LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );
HINSTANCE g_hinst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT( "Class" );

int APIENTRY WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpszCmdParam , int nCmdShow )
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hinst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	WndClass.hCursor = LoadCursor( NULL , IDC_ARROW );
	WndClass.hIcon = LoadIcon( NULL , IDI_APPLICATION );
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &WndClass );

	hWnd = CreateWindow( lpszClass , lpszClass ,
						 WS_OVERLAPPEDWINDOW ,
						 CW_USEDEFAULT ,CW_USEDEFAULT , 
						 CW_USEDEFAULT , CW_USEDEFAULT , 
						 NULL , ( HMENU )NULL ,
						 hInstance , NULL );

	ShowWindow( hWnd , nCmdShow );

	while( GetMessage( &Message , NULL , 0 , 0 ) )
	{
		TranslateMessage( &Message );
		DispatchMessage( &Message );
	}

	return ( int )Message.wParam;
}

LRESULT CALLBACK WndProc( HWND hWnd , UINT iMessage , WPARAM wParam , LPARAM lParam )
{
// 	HDC hdc , MemDC;
// 	PAINTSTRUCT ps;
 	RECT rt = { 0 , 0 , 1000 , 1000 };
	static Tank t1;
	switch( iMessage )
	{
		case WM_CREATE:
			SetTimer( hWnd , 1 , 10 , NULL );
			hWndMain = hWnd;
			return 0;

		case WM_PAINT:

			HDC hdc , MemDC;
			PAINTSTRUCT ps;

			hdc = BeginPaint( hWnd , &ps );
			MemDC = CreateCompatibleDC( hdc );

			t1.Render(hWnd, g_hinst, hdc, MemDC, ps);
			return 0;

		case WM_LBUTTONDOWN:
			return 0;

		case WM_TIMER:
			InvalidateRect( hWnd , &rt , true );
			return 0;

		case WM_KEYDOWN:
			switch( wParam )
			{
				case VK_UP:
					t1.Move(UP);
					break;
				case VK_DOWN:
					t1.Move(DOWN);
					break;
				case VK_LEFT:
					t1.Move(LEFT);
					break;
				case VK_RIGHT:
					t1.Move(RIGHT);
					break;
				default:
					break;
			}
			return 0;


		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;

	}
	return ( DefWindowProc( hWnd , iMessage , wParam , lParam ) );
}