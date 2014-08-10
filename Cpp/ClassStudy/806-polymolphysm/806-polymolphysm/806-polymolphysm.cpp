// 806-polymolphysm.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DarkElf.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector <Character*> _characters;
	Elf _elf;
	DarkElf _darkElf;

	_characters.push_back( &_elf );
	_characters.push_back( &_darkElf );

	for( auto charac : _characters )
	{
		charac->SayMyName();
	}

	return 0;
}

