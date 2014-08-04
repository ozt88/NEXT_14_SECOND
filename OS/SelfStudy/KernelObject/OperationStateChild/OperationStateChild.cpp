// OperationStateChild.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	float num1 , num2;
	_fputts( _T( "Return Value Test\n" ) , stdout );
	_tscanf_s( _T( "%f %f" ) , &num1 , &num2 );

	if( num2 == 0 )
	{
		exit( -1 ); //or return -1;
	}

	_tprintf_s( _T( "Operation Result : %f \n" ) , num1 / num2 );

	return 1;
}

