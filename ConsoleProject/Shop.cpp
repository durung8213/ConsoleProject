#include "Shop.h"
#include "Item.h"
#include<iostream>
#include <Windows.h>
#include "Player.h"

Shop::Shop()
{
	SetItems();
	buyingItem.clear();
}

Shop::~Shop()
{
}



void Shop::SetItems()
{
	AddItem(Item(ItemType::ITEM_ARMOR, "우단 면포", "얇은 면으로 만들어진 법사 옷", Effect::DEF, 36, 3500, 1));
	AddItem(Item(ItemType::ITEM_ARMOR, "강철 갑옷", "두터운 갑옷으로 둘러진 전사 옷",Effect::DEF, 45, 3500, 1));
	AddItem(Item(ItemType::ITEM_WEAPON, "나무 지팡이", "단단한 나무 조각으로 만들어진 법사 지팡이",Effect::ATK, 36, 2500, 1));
	AddItem(Item(ItemType::ITEM_WEAPON, "강철 도끼", "철로 만들어진 전사용 도끼",Effect::ATK, 45, 3000, 1));
	AddItem(Item(ItemType::ITEM_RING, "사파이어 반지", "파아란 보석이 박힌 마력의 반지",Effect::MP, 100, 4000, 1));
	AddItem(Item(ItemType::ITEM_RING, "루비 반지", "붉은 빛이 도는 투력의 반지",Effect::ATK, 100, 4000, 1));
	AddItem(Item(ItemType::ITEM_POTION, "포션", "HP를 50 회복시켜주는 붉은 물약",Effect::HP, 50, 800, 5));
	AddItem(Item(ItemType::ITEM_POTION, "에테르", "MP를 40 회복시켜주는 푸른 물약",Effect::MP, 40, 1000, 3));
}

void Shop::DisplayItems(GameEnums::ItemType type)
{
	showList.clear();
	cout << "================================= 아이템 목록 =================================" << endl;
	for (int i = 0; i < items.size(); i++)
	{
		const Item& item = items[i];
		if (item.GetType() == type)
		{
			showList.push_back(i + 1);
			cout << i + 1 << " . " << item.GetName() << " - " << item.GetDesc()
				<< "  가격 : " << item.GetPrice() << "  개수 : " << item.GetCount()<< endl;
		}
	}
}

//플레이어에게 구매한 아이템 표시
void Shop::DisplayBuyItems()
{
	cout << "================================= 판매한 아이템 목록 =================================" << endl;
	for (int i = 0; i < buyingItem.size(); i++)
	{
		const Item& item = buyingItem[i];
		cout << i + 1 << " . " << item.GetName() << " - " << item.GetDesc()
			<< "  가격 : " << item.GetPrice() << "  개수 : " <<item.GetCount()<< endl;
	}

}

Item* Shop::BuyItem(GameEnums::ItemType type, const int index, const int gill)
{
	Item* item = &items[index];
	if (item->GetCount() < 1)
	{
		cout << "더이상 구매할 수 없습니다." << endl;
		Sleep(900);
		return NULL;
	}
	else if (index >= items.size())
	{
		cout << "잘못된 입력값입니다." << endl;
		Sleep(900);
		return NULL;
	}
	for (const auto& it : showList)
	{
		if (it == index + 1)
		{
			if (item->GetPrice() <= gill)
			{
				cout << endl;
				cout << item->GetPrice() << "원으로 " << item->GetName() << "을 구매하셨습니다.";
				Sleep(900);
				return item;
			}
			else
			{
				cout << "소지금이 부족합니다!" << endl;
				Sleep(900);
				return NULL;
			}
		}
	}
	cout << "잘못된 입력값입니다." << endl;
	Sleep(900);
	return NULL;
}

void Shop::AddItem(const Item& item) 
{
	items.push_back(item);
}

void Shop::SetCount(const int index, const int count)
{
	items[index].SetCount(count);
}

void Shop::ReSellItem(const int index, Player& player)
{
	Item item = buyingItem[index];
	if (player.m_Inven.GetGill() >= item.GetPrice())
	{
		player.m_Inven.SetGill(player.m_Inven.GetGill() -item.GetPrice());
		cout << item.GetPrice() << "원으로 " << item.GetName() << "을 다시 구매하셨습니다.";
		Sleep(900);
		buyingItem.erase(buyingItem.begin() + index);
		player.m_Inven.AddItem(item);
	}
	
}
