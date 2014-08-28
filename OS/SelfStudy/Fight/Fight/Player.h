#pragma once
class CPlayer
{
public:
	CPlayer();
	CPlayer( int _hp , int _id , int _stage , bool _isMale );
	~CPlayer();

	void print();

private:
	int m_HP;
	int m_ID;
	bool m_isMale;
	int m_Stage;
};

