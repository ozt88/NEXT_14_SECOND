#pragma once
enum CharType
{
	CHARACTER,
	ELF,
	DARKELF,
};
class Character
{

public:
	Character();
	~Character();
	Character( const Character& src );
	virtual void SayMyName();
	CharType getType()
	{
		return m_Type;
	}

protected:
	CharType m_Type;
};

