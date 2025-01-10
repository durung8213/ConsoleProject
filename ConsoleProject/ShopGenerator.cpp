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
	//while문에서 반복 실행해야되는 코드부분.

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
	cout << "====================================   상점   =====================================" << endl;
	cout << "구매할 아이템 종류를 선택하세요.(1.방어구 2. 무기 3.장신구 4.아이템)" << endl;
	cout << "\t\t\t\t\t 0 : 나가기\t9: 인벤토리\t99 : 다시 구매" << endl;
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
			//다시 판매하는 상점 페이지로
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
			cout << "입력값이 잘못되었습니다." << endl;
			Sleep(900);
			return;
		}
	}

	m_shop->DisplayItems(itemType);
	cout << "구매할 아이템의 번호를 입력하세요." << endl;
	cout << "\t\t\t\t\t\t 0 : 뒤로 가기	" << endl;
	int num;
	cin >> num;
	//뒤로 가기
	if (num == 0) 
	{ 
		mLocation = Location::LOCATION_SHOP; 
	}
	else
	{
		//아이템 구매
		BuyItemFromShop(itemType, num);
		//장소 변경
		SetLocation(Location::LOCATION_SHOP);
	}

}

void ShopGenerator::SetInventoryPage()
{
	cout << "=================================  인벤토리  =================================" << endl;
	m_player->ShowInventory();
	cout << "소지금 : " << m_player->m_Inven.GetGill() << " 원" << endl;
	cout << "상점 : 1\t장비 장착 : 2\t장비 해제 : 3\t판매 : 4\t상태 보기 : 5\t나가기 : 9" << endl;
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		SetLocation(Location::LOCATION_SHOP);
	}
	else if (choice == 2)
	{
		cout << "장착할 아이템의 번호를 입력" << endl;
		cout << "\t\t\t\t\t\t 9 : 뒤로가기 " << endl;
		int itemNum;
		cin >> itemNum;
		if (itemNum == 9) return;
		EquipItemToPlayer(itemNum);
		mLocation = Location::LOCATION_INVENTORY;
	}
	else if (choice == 3)
	{
		m_player->ShowEquip();
		cout << "장착 해제할 아이템의 번호를 입력." << endl;
		cout << "\t\t\t\t\t\t 9 : 뒤로가기 " << endl;
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
	cout<<"===============================  인벤토리 판매  ================================" << endl;
	m_player->m_Inven.ShowInventory();
	cout << "판매할 아이템을 선택 " << endl;
	cout << "\t\t\t\t\t\t 0 : 맵으로 나가기	9: 인벤토리" << endl;
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
		cout << "==================판매한 아이템이 없습니다.==================" << endl;
		SetLocation(Location::LOCATION_SHOP);
		Sleep(1000);
		return;
	}
	m_shop->DisplayBuyItems();
	cout << "구매할 아이템의 번호를 입력하세요." << endl;
	cout << " \t\t\t\t\t\t0 : 뒤로 가기" << endl;
	int num;
	cin >> num;
	//뒤로 가기
	if (num == 0)
	{
		mLocation = Location::LOCATION_SHOP;
		return;
	}
	else
	{
		//아이템 구매
		m_shop->ReSellItem(num - 1,*m_player);
		//장소 변경
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
	//현재 소지금이 물건의 가격보다 값이 크다면 구매
	if (m_player->m_Inven.GetGill() >= boughtItem->GetPrice() && boughtItem->GetCount()>0)
	{
		cout << "아이템 구매 성공" << endl;
		m_player->AddItemToInventory(*boughtItem);
		cout << " 구매한 아이템 : " << boughtItem->GetName() << endl;
		//가격 감소
		m_player->m_Inven.SetGill(m_player->m_Inven.GetGill() - boughtItem->GetPrice());
		//개수 1 감소
		m_shop->SetCount(num - 1, boughtItem->GetCount() - 1);
		cout << "남은 금액 : " << m_player->m_Inven.GetGill() << "원" << endl;

	}
	else
	{
		cout << "현재 구매할 수 없습니다." << endl;
	}
}

void ShopGenerator::EquipItemToPlayer(const int num)
{
	m_player->EquipItem(num);
}

//상점 이미지
void ShopGenerator::PrintShopImage()
{
	//상점 배경 이미지.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■■■■■■■■■■■■■■■■■■■";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "■■■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■" << endl;

	//3
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■" << endl;

	//4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■"<<endl;

	//5
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■" << endl;

	//6
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■" << endl;

	//7
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 어두운 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 파랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// 파랑
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	
	cout << "■" << endl;

	//8
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■" << endl;

	//9
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//10
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■■■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "■"<<endl;

	//11
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■"; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■"<<endl;

	//12
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//13
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//14
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//15
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//16
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//17
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//18
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//빨강
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//19
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);	//검정
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//20
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//노랑
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//21
	cout << "■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "■■■■■■■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//하양
	cout << "■■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	cout << "■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout << "■" << endl;

	//22
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// 파랑
	cout<<"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

































}