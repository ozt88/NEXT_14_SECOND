// Fight.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

