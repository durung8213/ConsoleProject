#pragma once
#define _CRT_SECURE_NO_WARNING
#include <Windows.h>
#include<iostream>
#include<ctime>
#include "BSPNode.h"

using namespace std;

class DoubleBuffer
{
private:
	int g_nScreenIndex = 0;
	HANDLE g_hScreen[2];

public:
	DoubleBuffer();
	~DoubleBuffer() {}

	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint(int x, int y, string string);

};

