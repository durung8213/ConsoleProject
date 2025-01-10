#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<Windows.h>
#include "DoubleBuffer.h"
using namespace std;

class Map
{
public:
	Map() {}

	void PrintGrass();
	void PrintWall();
	void PrintRoad();
	void PrintEvent();
	void PrintShop();
	void PrintPlayer();
public:
	//string mapDraw = "";
private:
	void textcolor(int foreground, int background);
};

