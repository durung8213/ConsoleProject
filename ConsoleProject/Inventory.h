#pragma once
#include "Item.h"
#include <vector>

using namespace std;

class Player;

class Inventory
{
private:
	vector<Item> invenItems;
	Item equipArmor;
	Item equipWeapon;
	Item equipRing;

	int mGill;

public:
	Inventory();
	~Inventory();

	Player* player;

	void ShowInventory()const;
	void ShowEquip()const;

	void AddItem(const Item& item);
	Item SellItem(const int index);
	int GetItemSize();

	void EquipItem(const int index, Player* player);
	void EquipOff(const int index, Player* player);	//±¸Çö

	int GetGill() { return mGill; }
	void SetGill(const int price) { mGill = price; }

	void UseItem(const int index);
};

