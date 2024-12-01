#pragma once
#include<iostream>

class MapGenerator;

class MoveController
{
public:
	void MovePlayer(MapGenerator* mPtr, int& px, int& py, char input);
private:
	void SaveLastPos(MapGenerator* mPtr, int& px, int& py);
	void SaveLastInfo(MapGenerator* mPtr, int& px, int& py);

};

