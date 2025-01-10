#include "Map.h"
#include <string>

void Map::PrintGrass()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	//mapDraw += "бс";
	std::cout << "бс";
}

void Map::PrintWall()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	//mapDraw += "бс";
	std::cout << "бс";
}

void Map::PrintRoad()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "бс";
	//mapDraw += "бс";
}

void Map::PrintEvent()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "бс";
	//mapDraw += "бс";
}

void Map::PrintShop()
{
	textcolor(9, 14);
	std::cout << "б▀";
	//mapDraw += "б▀";
}

void Map::PrintPlayer()
{
	textcolor(14, 9);
	std::cout << "б┌";
	//mapDraw += "б┌";
}

void Map::textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}