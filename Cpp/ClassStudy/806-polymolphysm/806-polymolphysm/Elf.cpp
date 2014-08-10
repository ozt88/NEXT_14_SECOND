#include "stdafx.h"
#include "Elf.h"


Elf::Elf()
{
	m_Type = ELF;
}


Elf::~Elf()
{
}

void Elf::SayMyName()
{
	Character::SayMyName();
	printf( "My name is Elf. \n" );
}
