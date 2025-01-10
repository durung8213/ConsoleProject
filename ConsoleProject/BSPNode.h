#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<Windows.h>
#include<random>
#include<string>
#include "Map.h"

using namespace std;

#define minX 10
#define minY 10

const int mapSizeX = 44;
const int mapSizeY = 44;


struct Room
{
	int _x, _y, _w, _h;
};

struct Point
{
	int x, y;
};

struct Road
{
	Road(Point start, Point end) 
		: _x1(start.x), _y1(start.y), _x2(end.x), _y2(end.y) {}
	Road(int x1, int y1, int x2, int y2) 
		: Road(Point{ x1, y1 }, Point{ x2,y2 }) {}
	~Road() {}
	int _x1, _x2;
	int _y1, _y2;
};

class BSPNode
{
public:

	BSPNode(){}
	BSPNode(int x, int y, int w, int h);
	~BSPNode() { }

	void GetRoom(OUT vector<Room*>& rooms);
	void GetBSPNode(OUT vector<BSPNode*>& bspNode);

	BSPNode* GetParent() { return _parent; }
	Point GetCenter() { return Point{ _x +  _w / 2 , _y + _h / 2 }; }
	

	static BSPNode* CreateBSPNode(int x, int y, int w, int h);
	static int GetRandomNum(int min, int max);

	void Divide(BSPNode* parent);
	void Connect(BSPNode* root);
	void BSP();

	Room* MakeRoom(BSPNode* bspNode);
public:
	int map[mapSizeY][mapSizeX];
	bool IsBattle = false;
private:
	int _x, _y, _w, _h;

	BSPNode* _LChild = nullptr;
	BSPNode* _RChild = nullptr;
	BSPNode* _parent = nullptr;

	Room* _room = nullptr;
	Road* _road = nullptr;

};



