#include "Inventory.h"
#include "Player.h"
#include <Windows.h>

Inventory::Inventory()
{
	mGill = 10000;
}

Inventory::~Inventory()
{
}

//인벤토리 보여주기.
void Inventory::ShowInventory() const
{
	if (invenItems.empty())
	{
		cout << "인벤토리가 비어있음." << endl;
	}
	else
	{
		for (int i = 0; i < invenItems.size(); i++)
		{
			cout << (i + 1) << ": " << invenItems[i].GetName() <<"    " << invenItems[i].GetPrice() << " 원.\n";
		}
	}
}

//장비 소개
void Inventory::ShowEquip() const
{
	cout << " 1. 장착된 갑옷 : " << equipArmor.GetName()<<endl;
	cout << " 2. 장착된 무기 : " << equipWeapon.GetName()<<endl;
	cout << " 3. 장착된 장신구 : " << equipRing.GetName() << endl;
}

//인벤토리에 아이템 추가
void Inventory::AddItem(const Item& item)
{
	invenItems.push_back(item);
}

//아이템 판매
Item Inventory::SellItem(const int index)
{
	if (invenItems.empty())
	{
		cout << "인벤토리가 비어있습니다." << endl;
		return Item();
	}
	Item soldItem = invenItems[index - 1];

	int gold = soldItem.GetPrice() / 2;
	SetGill(GetGill() + gold);

	cout << soldItem.GetName() << "을 판매함.	금액 : " << gold << endl;

	invenItems.erase(invenItems.begin() + (index - 1));
	cout << "현재 금액 : " << mGill << " 원 . " << endl;
	Sleep(1300);
	return soldItem;


}

int Inventory::GetItemSize()
{
	return invenItems.size();
}

//아이템 장착
void Inventory::EquipItem(const int index, Player* player)
{
	if (invenItems.size() <= index - 1)
	{
		cout << "장착할 아이템이 없습니다!" << endl;
		Sleep(900);
		return;
	}
	Item equip = invenItems[index - 1];

	cout << equip.GetName() << " 장착!" << endl;
	switch (equip.GetType())
	{
	case ItemType::ITEM_ARMOR:
		//방어력 증가
		equipArmor = equip;
		player->SetDEF(player->GetDEF() + equip.GetEffPoint());
		break;
	case ItemType::ITEM_WEAPON:
		//공격력 증가.
		equipWeapon = equip;
		player->SetATK(player->GetATK() + equip.GetEffPoint());
		break;
	case ItemType::ITEM_RING:
		equipRing = equip;
		if (equip.GetEffect() == Effect::ATK)
			player->SetATK(player->GetATK() + equip.GetEffPoint());
		else if (equip.GetEffect() == Effect::MP)
			player->SetMP(player->GetMP() + equip.GetEffPoint());
		else { }
		break;
	default:
		break;
	}
	invenItems.erase(invenItems.begin() + index - 1);
	std::cout << "장착한 아이템이 인벤토리에서 삭제됩니다." << std::endl;
	Sleep(900);
}
//장비 해제
void Inventory::EquipOff(const int index, Player* player)
{
	if (index == 1 && equipArmor.GetName() != "")
	{
		cout << equipArmor.GetName() << " 해제!" << endl;
		player->SetDEF(player->GetDEF() - equipArmor.GetEffPoint());
		invenItems.push_back(equipArmor);
		equipArmor = Item();
	}
	else if (index == 2 && equipWeapon.GetName() != "")
	{
		cout << equipWeapon.GetName() << " 해제!" << endl;
		player->SetATK(player->GetATK() - equipWeapon.GetEffPoint());
		invenItems.push_back(equipWeapon);
		equipWeapon = Item();
	}
	else if (index == 3 && equipRing.GetName() != "")
	{
		cout << equipRing.GetName() << " 해제!" << endl;
		invenItems.push_back(equipRing);
		if(equipRing.GetEffect() == Effect::ATK)
			player->SetATK(player->GetATK() - equipRing.GetEffPoint());
		else if (equipRing.GetEffect() == Effect::MP)
			player->SetMP(player->GetMP() - equipRing.GetEffPoint());
		else { }
		equipRing = Item();
	}
	else
	{
		cout << "해제할 아이템이 없습니다." << endl;
	}
	Sleep(900);
}

void Inventory::UseItem(const int index)
{
	
	if (invenItems[index].GetType() != ItemType::ITEM_POTION)
	{
		return;
	}

	if (invenItems[index].GetEffect() == Effect::HP)
	{
		cout << "플레이어의 체력을 " << invenItems[index].GetEffPoint() << " 만큼 회복합니다." << endl;
		Sleep(900);
		player->SetHP(player->GetHP() + invenItems[index].GetEffPoint());
	}
	else if (invenItems[index].GetEffect() == Effect::MP)
	{
		cout << "플레이어의 마력을 " << invenItems[index].GetEffPoint() << " 만큼 회복합니다." << endl;
		Sleep(900);
		player->SetMP(player->GetMP() + invenItems[index].GetEffPoint());
	}
	else if (invenItems[index].GetEffect() == Effect::ATK)
	{
		cout << "플레이어의 공격력을 " << invenItems[index].GetEffPoint() << " 만큼 증가합니다." << endl;
		Sleep(900);
		player->SetATK(player->GetATK() + invenItems[index].GetEffPoint());
	}
	else
	{

	}

	invenItems.erase(invenItems.begin() + index);

}
