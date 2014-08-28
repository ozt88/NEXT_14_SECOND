#pragma once
#include "Player.h"
#define NAME_SIZE 100
#define PLAYER_NUM 5

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();
	void SaveData();
	void LoadData();
	void FindAndPrint();
private:
	
	CPlayer m_PlayerList[PLAYER_NUM];
	TCHAR m_DataName[NAME_SIZE];
};

