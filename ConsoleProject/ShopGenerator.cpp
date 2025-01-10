#include "ShopGenerator.h"
#include "Windows.h"
#include <conio.h>
#include <iostream>


ShopGenerator::ShopGenerator()
{
	m_shop = new Shop();
	mLocation = GameEnums::Location::LOCATION_SHOP;
}

ShopGenerator::~ShopGenerator()
{
	delete m_shop;
	m_shop = nullptr;
}

void ShopGenerator::UpdateShop()
{
	//while������ �ݺ� �����ؾߵǴ� �ڵ�κ�.

	system("cls");
	PrintShopImage();

	switch (mLocation)
	{
	case Location::LOCATION_SHOP:
		SetShopPage();
		break;
	case Location::LOCATION_SELL_INVENTORY:
		SetSellInventoryPage();
		break;
	case Location::LOCATION_INVENTORY:
		SetInventoryPage();
		break;
	case Location::LOCATION_MAP:
		IsOut = true;
		mLocation = Location::LOCATION_SHOP;
		break;
	case Location::LOCATION_RESELL_SHOP:
		SetReSellShopPage();
		break;
	default:
		break;
	}
}

void ShopGenerator::SetShopPage()
{
	int select; 
	cout << "====================================   ����   =====================================" << endl;
	cout << "������ ������ ������ �����ϼ���.(1.�� 2. ���� 3.��ű� 4.������)" << endl;
	cout << "\t\t\t\t\t 0 : ������\t9: �κ��丮\t99 : �ٽ� ����" << endl;
	cin >> select;

	GameEnums::ItemType itemType;

	if (select == 1)
	{
		itemType = GameEnums::ItemType::ITEM_ARMOR;
	}
	else if (select == 2)
	{
		itemType = GameEnums::ItemType::ITEM_WEAPON;
	}
	else if (select == 3)
	{
		itemType = GameEnums::ItemType::ITEM_RING;
	}
	else if (select == 4)
	{
		itemType = GameEnums::ItemType::ITEM_POTION;
	}
	else
	{
		if (select == 0)
		{
			mLocation = Location::LOCATION_MAP;
			return;
		}
		else if (select == 99)
		{
			//�ٽ� �Ǹ��ϴ� ���� ��������
			SetLocation(Location::LOCATION_RESELL_SHOP);
			return;
		}
		else if (select == 9)
		{
			mLocation = Location::LOCATION_INVENTORY;
			return;
		}
		else
		{
			cout << "�Է°��� �߸��Ǿ����ϴ�." << endl;
			Sleep(900);
			return;
		}
	}

	m_shop->DisplayItems(itemType);
	cout << "������ �������� ��ȣ�� �Է��ϼ���." << endl;
	cout << "\t\t\t\t\t\t 0 : �ڷ� ����	" << endl;
	int num;
	cin >> num;
	//�ڷ� ����
	if (num == 0) 
	{ 
		mLocation = Location::LOCATION_SHOP; 
	}
	else
	{
		//������ ����
		BuyItemFromShop(itemType, num);
		//��� ����
		SetLocation(Location::LOCATION_SHOP);
	}

}

void ShopGenerator::SetInventoryPage()
{
	cout << "=================================  �κ��丮  =================================" << endl;
	m_player->ShowInventory();
	cout << "������ : " << m_player->m_Inven.GetGill() << " ��" << endl;
	cout << "���� : 1\t��� ���� : 2\t��� ���� : 3\t�Ǹ� : 4\t���� ���� : 5\t������ : 9" << endl;
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		SetLocation(Location::LOCATION_SHOP);
	}
	else if (choice == 2)
	{
		cout << "������ �������� ��ȣ�� �Է�" << endl;
		cout << "\t\t\t\t\t\t 9 : �ڷΰ��� " << endl;
		int itemNum;
		cin >> itemNum;
		if (itemNum == 9) return;
		EquipItemToPlayer(itemNum);
		mLocation = Location::LOCATION_INVENTORY;
	}
	else if (choice == 3)
	{
		m_player->ShowEquip();
		cout << "���� ������ �������� ��ȣ�� �Է�." << endl;
		cout << "\t\t\t\t\t\t 9 : �ڷΰ��� " << endl;
		int num;
		cin >> num;
		if (num == 9) return;
		m_player->EquipOffItem(num);
		SetLocation(Location::LOCATION_INVENTORY);
	}
	else if (choice == 4)
	{
		SetLocation(Location::LOCATION_SELL_INVENTORY);
	}
	else if (choice == 5)
	{
		m_player->ShowStatus();
	}
	else if (choice == 9)
	{
		SetLocation(Location::LOCATION_MAP);
	}
	else
	{
		return;
	}
}

void ShopGenerator::SetSellInventoryPage()
{
	cout<<"===============================  �κ��丮 �Ǹ�  ================================" << endl;
	m_player->m_Inven.ShowInventory();
	cout << "�Ǹ��� �������� ���� " << endl;
	cout << "\t\t\t\t\t\t 0 : ������ ������	9: �κ��丮" << endl;
	int itemNum;
	cin >> itemNum;

	if (itemNum == 0)
	{
		mLocation = Location::LOCATION_MAP;
	}
	else if (itemNum == 9)
	{
		mLocation = Location::LOCATION_INVENTORY;
	}
	else if (itemNum > 0 && itemNum <= m_player->m_Inven.GetItemSize())
	{
		Item item = m_player->SellItem(itemNum);
		if (item.GetName() == "")
			return;
		m_shop->buyingItem.push_back(item);
		m_player->ShowInventory();
	}
	else
	{
	}
}

void ShopGenerator::SetReSellShopPage()
{
	if (m_shop->buyingItem.empty())
	{
		cout << "==================�Ǹ��� �������� �����ϴ�.==================" << endl;
		SetLocation(Location::LOCATION_SHOP);
		Sleep(1000);
		return;
	}
	m_shop->DisplayBuyItems();
	cout << "������ �������� ��ȣ�� �Է��ϼ���." << endl;
	cout << " \t\t\t\t\t\t0 : �ڷ� ����" << endl;
	int num;
	cin >> num;
	//�ڷ� ����
	if (num == 0)
	{
		mLocation = Location::LOCATION_SHOP;
		return;
	}
	else
	{
		//������ ����
		m_shop->ReSellItem(num - 1,*m_player);
		//��� ����
		SetLocation(Location::LOCATION_INVENTORY);
	}
}


void ShopGenerator::DisplayShopItems(GameEnums::ItemType itemKind)
{
	m_shop->DisplayItems(itemKind);
}

void ShopGenerator::BuyItemFromShop(GameEnums::ItemType itemKind, int num)
{

	Item* boughtItem = m_shop->BuyItem(itemKind, num - 1, m_player->m_Inven.GetGill());
	if (boughtItem == NULL)
	{
		SetLocation(Location::LOCATION_SHOP);
		return;
	}
	//���� �������� ������ ���ݺ��� ���� ũ�ٸ� ����
	if (m_player->m_Inven.GetGill() >= boughtItem->GetPrice() && boughtItem->GetCount()>0)
	{
		cout << "������ ���� ����" << endl;
		m_player->AddItemToInventory(*boughtItem);
		cout << " ������ ������ : " << boughtItem->GetName() << endl;
		//���� ����
		m_player->m_Inven.SetGill(m_player->m_Inven.GetGill() - boughtItem->GetPrice());
		//���� 1 ����
		m_shop->SetCount(num - 1, boughtItem->GetCount() - 1);
		cout << "���� �ݾ� : " << m_player->m_Inven.GetGill() << "��" << endl;

	}
	else
	{
		cout << "���� ������ �� �����ϴ�." << endl;
	}
}

void ShopGenerator::EquipItemToPlayer(const int num)
{
	m_player->EquipItem(num);
}

//���� �̹���
void ShopGenerator::PrintShopImage()
{
	//���� ��� �̹���.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "���������������������������������������������" << endl;
	
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���������������������";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "���������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��" << endl;

	//3
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "��������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��" << endl;

	//4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��"<<endl;

	//5
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��" << endl;

	//6
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "��������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��" << endl;

	//7
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// ��ο� �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �Ķ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �Ķ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	
	cout << "��" << endl;

	//8
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��" << endl;

	//9
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//10
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "�����������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "��"<<endl;

	//11
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��"<<endl;

	//12
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//13
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//14
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//15
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//16
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//17
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//18
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//19
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//����
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//20
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "�����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//���
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//21
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "����������������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "����������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "�������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//�Ͼ�
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout << "��" << endl;

	//22
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// �Ķ�
	cout<<"���������������������������������������������" << endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

































}