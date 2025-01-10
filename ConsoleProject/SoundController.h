#pragma once
#include <iostream>
#include<Windows.h>
#include<stdio.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

class SoundController
{
public:
	SoundController() {}
	~SoundController() {}

	void PlayMainBGM();
	void PlayMapBGM();
	void PlayBattleBGM();
	void PlayShopBGM();
	void PlayVictoryBGM();

private :
	std::string lastMusic;
};

