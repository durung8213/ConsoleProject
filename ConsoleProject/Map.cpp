#include "Map.h"

void Map::PrintGrass()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "��";
}

void Map::PrintWall()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	std::cout << "��";
}

void Map::PrintRoad()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "��";
}

void Map::PrintEvent()
{

}

void Map::PrintShop()
{
}

void Map::PrintPlayer()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	std::cout << "��";
}
