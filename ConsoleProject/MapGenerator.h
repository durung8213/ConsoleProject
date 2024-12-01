#pragma once
#include "BSPNode.h"
#include "MoveController.h"
#include<iostream>
#include<conio.h>


struct playerPos
{
	int x = 20;
	int y = 25;
};

class MapGenerator
{
public:
	unique_ptr<BSPNode>bsp{ new BSPNode() };
	unique_ptr<Map>mapPtr{ new Map() };
	unique_ptr<MoveController>  movePtr{ new MoveController() };
	//플레이어 위치 초기화.
	playerPos p_Pos;
	
public:
	MapGenerator();
	~MapGenerator(){}

	void consoleInit();
	void GenerateBSP();
	
	void PrintMap();
	void PrintShop();
	
	void GetIsSafe();
	void SetPlayer();
	void UpdatePos();

	void ClearMap();

	short lastInfo = 1;
	short lastX;
	short lastY;
	
};