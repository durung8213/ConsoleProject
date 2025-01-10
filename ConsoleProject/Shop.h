#pragma once
#include<vector>
#include"Item.h"


using namespace GameEnums;

class Player;

class Shop
{
public:
	vector<Item> buyingItem;
private:
	vector<Item> items;
	vector<int> showList;

public:
	Shop();
	~Shop();

	void SetItems();
	void DisplayItems(ItemType type);
	void DisplayBuyItems();
	Item* BuyItem(ItemType type, const int index, const int gill);
	void AddItem(const Item& item);
	void SetCount(const int index, const int count);

	void ReSellItem(const int index, Player& player);

};

