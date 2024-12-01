#pragma once
#include <iostream>
#include<vector>
#include<string>
#include "GameEnums.h"
#include "Player.h"

using namespace std;
using namespace GameEnums;

class Monster
{
private:
	int m_money;
	string m_trophy;
	Skill m_skill;

	int m_HP;
	int m_ATK;
	int m_DEF;
	int m_CRT;
public:
	void Attack(Player& player);
	void Skill(Player& player);
	void Dead();
	int DropItem();

};

