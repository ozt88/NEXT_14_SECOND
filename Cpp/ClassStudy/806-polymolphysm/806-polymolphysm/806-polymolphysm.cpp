// 806-polymolphysm.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

