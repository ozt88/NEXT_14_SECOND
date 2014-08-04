// KerObjProb2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD n = 0;
	while( n < 100 )
	{
		for( DWORD i = 0; i < 10000; i++ )
		{
			for( DWORD j = 0; j < 10000; j++ )
			{
				//Busy Waiting....
			}
		}

		_fputts( _T( "KerObjProb2.exe\n") , stdout );
		n++;
	}
	return 0;
}

