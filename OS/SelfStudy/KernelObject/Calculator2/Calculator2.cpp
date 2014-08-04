// Calculator2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

enum
{
	DIV = 1 , MUL , ADD , MIN , ELSE , EXIT
};

DWORD ShowMenu();
void Divide( double , double );
void Multiple( double , double );
void Add( double , double );
void Min( double , double );

int _tmain( int argc , _TCHAR* argv[] )
{
	STARTUPINFO si = { 0 , };
	PROCESS_INFORMATION pi;
	si.cb = sizeof( si );

	TCHAR command[] = _T( "calc.exe" );
	SetCurrentDirectory( _T( "C:\\WINDOWS\\system32" ) );

	DWORD sel;
	double num1 , num2;

	while( true )
	{
		sel = ShowMenu();
		if( sel == EXIT )
			return 0;

		if( sel != ELSE )
		{
			_fputts( _T( "Input Num1 Num2: " ) , stdout );
			_tscanf_s( _T( "%lf %lf" ) , &num1 , &num2 );
		}

		switch( sel )
		{
			case DIV:
				Divide( num1 , num2 );
				break;
			case MUL:
				Multiple( num1 , num2 );
				break;
			case ADD:
				Add( num1 , num2 );
				break;
			case MIN:
				Min( num1 , num2 );
				break;
			case ELSE:
				ZeroMemory( &pi , sizeof( pi ) );
				CreateProcess(
					NULL , command , NULL , NULL , TRUE ,
					0 , NULL , NULL , &si , &pi
					);
				//CloseHandle( pi.hProcess );
				//CloseHandle( pi.hThread );
				break;

			default:
				break;
		}

	}

	return 0;
}


DWORD ShowMenu()
{
	DWORD sel = 0;

	_fputts( _T( "------MENU------\n" ) , stdout );
	_fputts( _T( "num 1: Divide\n" ) , stdout );
	_fputts( _T( "num 2: Multiple\n" ) , stdout );
	_fputts( _T( "num 3: Add\n" ) , stdout );
	_fputts( _T( "num 4: Minus\n" ) , stdout );
	_fputts( _T( "num 5: Any Other Operations\n" ) , stdout );
	_fputts( _T( "num 6: EXIT\n" ) , stdout );
	_fputts( _T( "SELECTION >>" ) , stdout );
	fflush( stdin );
	_tscanf_s( _T( "%d" ) , &sel );

	return sel;
}

void Divide( double num1 , double num2 )
{
	_tprintf( _T( "%f / %f = %f \n\n" ) , num1 , num2 , num1 / num2 );
}

void Multiple( double num1 , double num2 )
{
	_tprintf( _T( "%f * %f = %f \n\n" ) , num1 , num2 , num1 * num2 );
}

void Add( double num1 , double num2 )
{
	_tprintf( _T( "%f + %f = %f \n\n" ) , num1 , num2 , num1 + num2 );

}

void Min( double num1 , double num2 )
{
	_tprintf( _T( "%f - %f = %f \n\n" ) , num1 , num2 , num1 - num2 );
}
