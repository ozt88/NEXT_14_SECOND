// KerObjProb1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = { 0 , };
	PROCESS_INFORMATION pi;
	si.cb = sizeof( si );

	TCHAR command[] = _T( "KerObjProb2.exe" );
	CreateProcess( NULL , command , NULL , NULL , TRUE ,
				   0 , NULL , NULL , &si , &pi );
	CloseHandle( pi.hProcess );
	return 0;
}

