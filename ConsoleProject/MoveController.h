#pragma once
#include<iostream>

class MapGenerator;

class MoveController
{
public:
	bool IsShop = false;
	bool IsBattle = false;
	bool GoStart = false;
	void MovePlayer(MapGenerator* mPtr, int& px, int& py, char input);
private:
	void SaveLastPos(MapGenerator* mPtr, int& px, int& py);
	void DetactObject(MapGenerator* mPtr, int& px, int& py);

};

