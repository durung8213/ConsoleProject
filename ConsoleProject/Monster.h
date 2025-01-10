#pragma once
#include <iostream>
#include<vector>
#include<string>
#include "GameEnums.h"
#include "Player.h"
#include "SoundController.h"

using namespace std;
using namespace GameEnums;

class Monster
{
public:
	int GetGill() { return m_money; }
	Item GetTrophy() { return m_trophy; }
	int GetHP() { return m_HP; }
	int GetATK() { return m_ATK; }
	string GetName() { return m_name; }

	void SetHP(int hp) { m_HP = hp; }

	SoundController* sc = new SoundController();

	Monster(const int money, const string& name);
	~Monster() { delete sc; }

private:
	int m_money;
	Item m_trophy;
	Skill m_skill;
	string m_name;
	bool m_life = true;


	int m_HP = 80;
	int m_ATK = 30;
	int m_DEF = 10;
	int m_CRT = 15;
public:
	void Attack(Player& player);
	void Skill(Player& player);
	void Dead();
	int DropItem();

};
