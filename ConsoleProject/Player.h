#pragma once
#include "Character.h"
#include <iostream>
#include <vector>

class Monster;

class Player : public Character
{
public:
	Inventory m_Inven;

	Player(const string& name, const Job job, const string& sk1, const string& sk2, const int hp,
		const int mp, const int atk, const int def, const double crt);
	~Player(){}

	Item SellItem(const int itemNum);
	void EquipItem(const int num);
	void EquipOffItem(const int num);

	void AddItemToInventory(const Item& item);

	void ShowInventory()const;
	void ShowStatus();
	void ShowEquip()const;

	void Attack(Monster* m);
	bool Skill(Monster* m, const string& sk);
	void UseItem();



private:

	bool m_Death = false;
	int LBPoint = 0;
};