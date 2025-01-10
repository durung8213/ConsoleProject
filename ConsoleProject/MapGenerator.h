#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "BSPNode.h"
#include "MoveController.h"
#include <iostream>
#include <conio.h>


struct playerPos
{
	int x = mapSizeX / 2;
	int y = mapSizeY / 2;
};

struct ShopPos
{
	int x;
	int y;
};
class MapGenerator
{
public:
	unique_ptr<BSPNode>bsp{ new BSPNode() };
	unique_ptr<Map>mapPtr{ new Map() };
	unique_ptr<MoveController>  movePtr{ new MoveController() };
	//플레이어 위치
	playerPos p_Pos;
	//Shop 위치
	ShopPos shop1Pos;
	ShopPos shop2Pos;
public:
	MapGenerator();
	~MapGenerator(){}

	void consoleInit();
	void GenerateBSP();
	
	void PrintMap();
	
	void GetIsSafe();
	void SetPlayer();
	void UpdatePos();

	void ClearMap();
	bool IsBattleStart();

public:

	short lastInfo = 1;
	short lastX;
	short lastY;

};