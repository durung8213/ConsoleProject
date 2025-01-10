#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;
class StartScene
{
public:
	bool GameStart = false;
	bool GameOver = false;

	void SelectMenu();
private:
	void ShowMainScreen();
	void SetMenu(const vector<string>& options, int selectedIndex);
	void ShowGameInfo();

private:
	vector<string>startMenu = 
	{
		"���� ����",
		"���� ����"
	};
	int selectedIndex = 0;
};

