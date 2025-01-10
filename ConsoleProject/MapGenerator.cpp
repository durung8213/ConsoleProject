#include "MapGenerator.h"
#include<iostream>
#include <string>

MapGenerator::MapGenerator()
{
	// ���� 2���� ��ġ�� �������� �ʱ�ȭ.
	shop1Pos.x = bsp->GetRandomNum(3, 35);
	shop1Pos.y = bsp->GetRandomNum(3, 35);
	shop2Pos.x = bsp->GetRandomNum(3, 35);
	shop2Pos.y = bsp->GetRandomNum(3, 35);
}

void MapGenerator::consoleInit()
{
	system("mode con:cols=95 lines=50 | title Fantasy TRPG");
	return;
}

void MapGenerator::GenerateBSP()
{
	bsp->BSP();
}

void MapGenerator::PrintMap()
{
	for (int i = 0; i < mapSizeX; i++)
	{
		for (int k = 0; k < mapSizeY; k++)
		{
			if (bsp->map[i][k] == 0)
			{
				// 0 -> �� �κ� ��ĥ
				mapPtr->PrintWall();
			}
			else if (bsp->map[i][k] == 1)
				// 1 -> �̵�, ��ġ ������ �� �κ�
				mapPtr->PrintGrass();
			else if (bsp->map[i][k] == 2)
				// 2 -> �̵��� ������ �� �κ�
				mapPtr->PrintRoad();
			else if (bsp->map[i][k] == 3)
				// 3 -> �÷��̾� �̵�.
				mapPtr->PrintPlayer();
				// 4 -> shop ��ġ.
			else if (bsp->map[i][k] == 4)
				mapPtr->PrintShop();
		}
		cout << endl;
	}
	cout << endl;
}

void MapGenerator::SetPlayer()
{
	if (movePtr->IsShop)
	{
		return;
	}
	bsp->map[p_Pos.y][p_Pos.x] = 3;
}

void MapGenerator::UpdatePos()
{
	bsp->map[lastY][lastX] = lastInfo;
}

void MapGenerator::GetIsSafe()
{
	int pInfo = bsp->map[p_Pos.y][p_Pos.x];
	int s1 = bsp->map[shop1Pos.y][shop1Pos.x];
	int s2 = bsp->map[shop2Pos.y][shop2Pos.x];
	

	if (pInfo == 0 || pInfo == 2)
	{
		//�÷��̾� or ���� ���� ����+�� ���� ���,
		p_Pos.x++;
		GenerateBSP();
		GetIsSafe();
	}
	else if (s1 == 0 || s1 == 2)
	{
		shop1Pos.x++;
		GetIsSafe();
	}
	else if (s2 == 0 || s2 == 2)
	{
		shop2Pos.x++;
		GetIsSafe();
	}
	else if (pInfo == 1 && s1 == 1 && s2 == 1)
	{
		lastX = p_Pos.x;
		lastY = p_Pos.y;
		bsp->map[shop1Pos.y][shop1Pos.x] = 4;
		bsp->map[shop2Pos.y][shop2Pos.x] = 4;
	}

}

void MapGenerator::ClearMap()
{
	Sleep(100);
	system("cls");
}

bool MapGenerator::IsBattleStart()
{
	int proba1 = bsp->GetRandomNum(1, 35);
	int proba2 = bsp->GetRandomNum(1, 35);

	if (proba1 == proba2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
