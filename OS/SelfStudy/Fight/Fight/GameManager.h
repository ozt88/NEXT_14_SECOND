#pragma once
#include "Player.h"
#define NAME_SIZE 100
#define PLAYER_NUM 5
#define MAX_HP 2000
#define ATTACK_COUNT 10

struct PlayerInfo
{
	int		m_HP;
	int		m_ID;
	bool	m_isMale;
	int		m_Stage;
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void						Init();
	void						SaveData();
	void						LoadData();
	void						FindAndPrint();
	void						Attack( CPlayer* from , CPlayer* to );
	static unsigned int WINAPI	WrapedThreadProc( LPVOID lpparam );
	DWORD						ThreadProc();
	void						Run();
	void						Clear();

private:
	int							m_HandleNum;
	std::vector <CPlayer*>		m_PlayerList;
	TCHAR						m_DataName[NAME_SIZE];
};

