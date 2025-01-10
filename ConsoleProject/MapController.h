#pragma once
#include "MapGenerator.h"

class MapController 
{
public:
	MapController();
	~MapController()
	{
		delete map;
		map = nullptr;
	}
	void ShowCurrentScene()const;
public:
	MapGenerator* map = new MapGenerator();
};

