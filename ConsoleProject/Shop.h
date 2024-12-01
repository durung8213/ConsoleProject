#pragma once
#include<vector>
#include"Item.h"

using namespace GameEnums;

class Shop
{
private:
	vector<Item>items;
	vector<Item> buyingItem;

public:
	Shop();
	~Shop();

	void SetItem();
	void DisplayItems(ItemType type)const;
	void DisplayBuyItems(ItemType type)const;
	Item* BuyItem(ItemType type, const int index, int& price);
	void AddItem(const Item& item);

	void ReSellItem(const int index, int& price);
};

