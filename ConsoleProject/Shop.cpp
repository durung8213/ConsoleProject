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
	AddItem(Item(ItemType::ITEM_ARMOR, "��� ����", "���� ������ ������� ���� ��", Effect::DEF, 36, 3500, 1));
	AddItem(Item(ItemType::ITEM_ARMOR, "��ö ����", "���Ϳ� �������� �ѷ��� ���� ��",Effect::DEF, 45, 3500, 1));
	AddItem(Item(ItemType::ITEM_WEAPON, "���� ������", "�ܴ��� ���� �������� ������� ���� ������",Effect::ATK, 36, 2500, 1));
	AddItem(Item(ItemType::ITEM_WEAPON, "��ö ����", "ö�� ������� ����� ����",Effect::ATK, 45, 3000, 1));
	AddItem(Item(ItemType::ITEM_RING, "�����̾� ����", "�ľƶ� ������ ���� ������ ����",Effect::MP, 100, 4000, 1));
	AddItem(Item(ItemType::ITEM_RING, "��� ����", "���� ���� ���� ������ ����",Effect::ATK, 100, 4000, 1));
	AddItem(Item(ItemType::ITEM_POTION, "����", "HP�� 50 ȸ�������ִ� ���� ����",Effect::HP, 50, 800, 5));
	AddItem(Item(ItemType::ITEM_POTION, "���׸�", "MP�� 40 ȸ�������ִ� Ǫ�� ����",Effect::MP, 40, 1000, 3));
}

void Shop::DisplayItems(GameEnums::ItemType type)
{
	showList.clear();
	cout << "================================= ������ ��� =================================" << endl;
	for (int i = 0; i < items.size(); i++)
	{
		const Item& item = items[i];
		if (item.GetType() == type)
		{
			showList.push_back(i + 1);
			cout << i + 1 << " . " << item.GetName() << " - " << item.GetDesc()
				<< "  ���� : " << item.GetPrice() << "  ���� : " << item.GetCount()<< endl;
		}
	}
}

//�÷��̾�� ������ ������ ǥ��
void Shop::DisplayBuyItems()
{
	cout << "================================= �Ǹ��� ������ ��� =================================" << endl;
	for (int i = 0; i < buyingItem.size(); i++)
	{
		const Item& item = buyingItem[i];
		cout << i + 1 << " . " << item.GetName() << " - " << item.GetDesc()
			<< "  ���� : " << item.GetPrice() << "  ���� : " <<item.GetCount()<< endl;
	}

}

Item* Shop::BuyItem(GameEnums::ItemType type, const int index, const int gill)
{
	Item* item = &items[index];
	if (item->GetCount() < 1)
	{
		cout << "���̻� ������ �� �����ϴ�." << endl;
		Sleep(900);
		return NULL;
	}
	else if (index >= items.size())
	{
		cout << "�߸��� �Է°��Դϴ�." << endl;
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
				cout << item->GetPrice() << "������ " << item->GetName() << "�� �����ϼ̽��ϴ�.";
				Sleep(900);
				return item;
			}
			else
			{
				cout << "�������� �����մϴ�!" << endl;
				Sleep(900);
				return NULL;
			}
		}
	}
	cout << "�߸��� �Է°��Դϴ�." << endl;
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
		cout << item.GetPrice() << "������ " << item.GetName() << "�� �ٽ� �����ϼ̽��ϴ�.";
		Sleep(900);
		buyingItem.erase(buyingItem.begin() + index);
		player.m_Inven.AddItem(item);
	}
	
}
