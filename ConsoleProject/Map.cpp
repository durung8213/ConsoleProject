#include "Map.h"
#include <string>

void Map::PrintGrass()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	//mapDraw += "��";
	std::cout << "��";
}

void Map::PrintWall()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	//mapDraw += "��";
	std::cout << "��";
}

void Map::PrintRoad()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "��";
	//mapDraw += "��";
}

void Map::PrintEvent()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "��";
	//mapDraw += "��";
}

void Map::PrintShop()
{
	textcolor(9, 14);
	std::cout << "��";
	//mapDraw += "��";
}

void Map::PrintPlayer()
{
	textcolor(14, 9);
	std::cout << "��";
	//mapDraw += "��";
}

void Map::textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}