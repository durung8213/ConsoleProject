#pragma once
#include "Item.h"
#include <vector>

using namespace std;

class Inventory
{
private:
	vector<Item> items;
	Item equipArmor;
	Item equipWeapon;
	Item equipRing;


public:
	Inventory();
	~Inventory();

	void ShowInventory()const;
	void AddItem(const Item& item);
	Item SellItem(const int index, int& price);

	void EquipItem(const int index);
	void EquipOff(const Item& item);	//±¸Çö
	Item GetEquippedArmor()const;
	Item GetEquippedWeapon()const;
	Item GetEquippedRing()const;


};

