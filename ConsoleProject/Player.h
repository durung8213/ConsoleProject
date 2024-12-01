#pragma once
#include "Character.h"
#include<iostream>



#define PLAYER_SIZE 3;

class Player : public Character
{
public:

private:
	string m_name = "BlackMage";
	Job m_job = Job::BLACKMAGE;
	Inventory m_inventory;
	Skill m_skill = Skill::FIRE;
	int m_money = 10000;

	int m_HP = 100;
	int m_MP = 100;
	int m_ATK = 30;
	int m_DEF = 40;
	double m_CRT = 0.7;

	bool m_Death = false;
	int LBPoint = 0;
};