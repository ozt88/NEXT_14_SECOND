#include "stdafx.h"
#include "Character.h"


Character::Character()
{
	m_Type = CHARACTER;
	printf( "CREATED!\n" );
}

Character::Character( const Character& src )
{
	m_Type = src.m_Type;
	printf( "COPYED!\n" );
}


Character::~Character()
{
}

void Character::SayMyName()
{
	printf_s( "My name is Character.\n" );
}
