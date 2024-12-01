#include "MapGenerator.h"
#include<iostream>

MapGenerator::MapGenerator()
{
}

void MapGenerator::consoleInit()
{
	system("mode con cols=40 lines=50 | title Fantasy TRPG");
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
				// 0 -> 벽 부분 색칠
				mapPtr->PrintWall();
			}
			else if (bsp->map[i][k] == 1)
				// 1 -> 이동, 설치 가능한 땅 부분
				mapPtr->PrintGrass();
			else if (bsp->map[i][k] == 2)
				// 2 -> 이동만 가능한 길 부분
				mapPtr->PrintRoad();
			else if (bsp->map[i][k] == 3)
				// 3 -> 플레이어 이동.
				mapPtr->PrintPlayer();
		}
		cout << endl;
	}
	cout << endl;
	
}

void MapGenerator::SetPlayer()
{
	bsp->map[p_Pos.y][p_Pos.x] = 3;
}

void MapGenerator::UpdatePos()
{
	bsp->map[lastY][lastX] = lastInfo;
}

void MapGenerator::PrintShop()
{
}

void MapGenerator::GetIsSafe()
{
	int info = bsp->map[p_Pos.y][p_Pos.x];

	if (info == 0 || info == 2)
	{
		//플레이어 or 상점 스폰 지역이 벽일 경우,
		p_Pos.x++;
		//GenerateBSP();
		GetIsSafe();
	}
	else
	{
		// 1. ground에 스폰.
		lastX = p_Pos.x;
		lastY = p_Pos.y;
	}


}

void MapGenerator::ClearMap()
{
	Sleep(100);
	system("cls");
}
