#include "Shop.h"
#include<iostream>

Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::SetItem()
{
}

void Shop::DisplayItems(GameEnums::ItemType type) const
{

}

//�÷��̾�� ������ ������ ǥ��
void Shop::DisplayBuyItems(ItemType type) const
{
	
}

Item* Shop::BuyItem(GameEnums::ItemType type, const int index, int& price)
{
	return nullptr;
}

void Shop::AddItem(const Item& item)
{
	items.push_back(item);
}

void Shop::ReSellItem(const int index, int& price)
{

}
