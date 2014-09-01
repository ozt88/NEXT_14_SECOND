#pragma once
class CPlayer
{
public:
	CPlayer();
	CPlayer( int _hp , int _id , int _stage , bool _isMale );
	~CPlayer();

	void				print();
	void				Attacking() {m_HP +=100;}
	void				Attacked() {m_HP -=70;}
	int					GetId() {return m_ID; }
	int					GetHP() {return m_HP; }
	int					GetStage() {return m_Stage; }
	bool				GetIsMale() {return m_isMale; }
	CRITICAL_SECTION*	GetLock() { return m_Lock; }

private:
	int					m_HP;
	int					m_ID;
	bool				m_isMale;
	int					m_Stage;
	CRITICAL_SECTION*	m_Lock;
};

