// Fight.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

