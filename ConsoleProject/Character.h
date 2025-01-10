#pragma once
#include<iostream>
#include<vector>
#include "GameEnums.h"
#include "Inventory.h"
#include <map>


using namespace std;
using namespace GameEnums;
class Character
{
protected:
	string m_name;
	Job m_job;
	Inventory m_inventory;
	map<string, int> m_Skill;

	int m_HP=0;
	int m_MP=0;
	int m_ATK=0;
	int m_DEF=0;
	double m_CRT=0;
public:
	string GetName() { return this->m_name; }
	Job GetJob() { return this->m_job; }

	int GetHP() { return this->m_HP; }
	int GetMP() { return this->m_MP; }
	int GetATK() { return this->m_ATK; }
	int GetDEF() { return this->m_DEF; }
	double GetCRT() { return this->m_CRT; }
	map<string, int>& GetSkill() { return m_Skill; }

	void SetHP(int hp) { this->m_HP = hp; }
	void SetMP(int mp) { this->m_MP = mp; }
	void SetATK(int atk) { this->m_ATK = atk; }
	void SetDEF(int def) { this->m_DEF = def; }
	void SetName(const string& name) { this->m_name = name; }
};

