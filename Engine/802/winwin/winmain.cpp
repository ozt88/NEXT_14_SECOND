#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"

LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );
HINSTANCE g_hinst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT( "Class" );
std::list <GameObject*> gameObjs;
std::list <GameObject*> deleteObjs;

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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 0 , 0 , 1000 , 1000 };
	static Tank* player = new Tank();
	int randomValue = 100;
	int generater = 0;
	srand( time( NULL ) );

	switch( iMessage )
	{
		case WM_CREATE:
			SetTimer( hWnd , 1 , 100 , NULL );
			gameObjs.push_back( player );
			hWndMain = hWnd;
			return 0;

		case WM_PAINT:

			hdc = BeginPaint( hWnd , &ps );
			for( auto object : gameObjs)
			{
				object->Render( hWnd , g_hinst , hdc );
			}
			EndPaint( hWnd , &ps );

			return 0;

		case WM_LBUTTONDOWN:
			return 0;

		case WM_TIMER:

			if( randomValue > 100 ){--randomValue;}

			for( auto& object = gameObjs.begin(); object != gameObjs.end(); ++object )
			{
				(*object)->Update();
				if( ( *object )->IsDestroy() )
				{
					deleteObjs.push_back(*object);
				}
			}

			for( auto& deletes : deleteObjs )
			{
				gameObjs.remove( deletes );
				delete deletes;
			}
			deleteObjs.clear();
			InvalidateRect( hWnd , &rt , true );
			return 0;

		case WM_KEYDOWN:
			switch( wParam )
			{
				case VK_LEFT:
					player->Move( 0 );
					break;
				case VK_RIGHT:
					player->Move( 1 );
					break;
				case VK_UP:
					player->Move( 2 );
					break;
				case VK_DOWN:
					player->Move( 3 );
					break;
				case VK_SPACE:
					gameObjs.push_back(player->Attack(90));
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