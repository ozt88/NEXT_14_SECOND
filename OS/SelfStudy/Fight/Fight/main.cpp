// Fight.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager GM;
	GM.Init();
	GM.SaveData();
	//GM.LoadData();
	for( int i = 0; i < PLAYER_NUM; ++i )
	{
		GM.FindAndPrint();
	}
	return 0;
}

