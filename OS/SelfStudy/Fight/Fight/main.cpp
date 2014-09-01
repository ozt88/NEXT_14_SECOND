// Fight.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
    GameManager GM;
    GM.Init();
    GM.SaveData();
    GM.Clear();
    GM.LoadData();
    GM.Run();
    return 0;
}

