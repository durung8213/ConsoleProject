#pragma once
#include<iostream>
#include<vector>
#include "GameEnums.h"
#include "Inventory.h"
using namespace std;
using namespace GameEnums;
class Character
{
protected:
	string m_name;
	Job m_job;
	Inventory m_inventory;
	Skill m_skill;
	int m_money;

	int m_HP;
	int m_MP;
	int m_ATK;
	int m_DEF;
	int m_CRT;
public:
	string GetName() { return m_name; }
	Job GetJob() { return m_job; }

	int GetMoney(){ return m_money; }
	int GetHP() { return m_HP; }
	int GetMP() { return m_MP; }
	int GetATK() { return m_ATK; }
	int GetDEF() { return m_DEF; }
	int GetCRT() { return m_CRT; }
	

	void SetMoney(int money) { this->m_money = money; }
	void SetHP(int hp) { this->m_HP = hp; }
	void SetMP(int mp) { this->m_MP = mp; }
	void SetATK(int atk) { this->m_ATK = atk; }
	void SetDEF(int def) { this->m_DEF = def; }


};

