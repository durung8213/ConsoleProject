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

//�κ��丮 �����ֱ�.
void Inventory::ShowInventory() const
{
	if (invenItems.empty())
	{
		cout << "�κ��丮�� �������." << endl;
	}
	else
	{
		for (int i = 0; i < invenItems.size(); i++)
		{
			cout << (i + 1) << ": " << invenItems[i].GetName() <<"    " << invenItems[i].GetPrice() << " ��.\n";
		}
	}
}

//��� �Ұ�
void Inventory::ShowEquip() const
{
	cout << " 1. ������ ���� : " << equipArmor.GetName()<<endl;
	cout << " 2. ������ ���� : " << equipWeapon.GetName()<<endl;
	cout << " 3. ������ ��ű� : " << equipRing.GetName() << endl;
}

//�κ��丮�� ������ �߰�
void Inventory::AddItem(const Item& item)
{
	invenItems.push_back(item);
}

//������ �Ǹ�
Item Inventory::SellItem(const int index)
{
	if (invenItems.empty())
	{
		cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
		return Item();
	}
	Item soldItem = invenItems[index - 1];

	int gold = soldItem.GetPrice() / 2;
	SetGill(GetGill() + gold);

	cout << soldItem.GetName() << "�� �Ǹ���.	�ݾ� : " << gold << endl;

	invenItems.erase(invenItems.begin() + (index - 1));
	cout << "���� �ݾ� : " << mGill << " �� . " << endl;
	Sleep(1300);
	return soldItem;


}

int Inventory::GetItemSize()
{
	return invenItems.size();
}

//������ ����
void Inventory::EquipItem(const int index, Player* player)
{
	if (invenItems.size() <= index - 1)
	{
		cout << "������ �������� �����ϴ�!" << endl;
		Sleep(900);
		return;
	}
	Item equip = invenItems[index - 1];

	cout << equip.GetName() << " ����!" << endl;
	switch (equip.GetType())
	{
	case ItemType::ITEM_ARMOR:
		//���� ����
		equipArmor = equip;
		player->SetDEF(player->GetDEF() + equip.GetEffPoint());
		break;
	case ItemType::ITEM_WEAPON:
		//���ݷ� ����.
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
	std::cout << "������ �������� �κ��丮���� �����˴ϴ�." << std::endl;
	Sleep(900);
}
//��� ����
void Inventory::EquipOff(const int index, Player* player)
{
	if (index == 1 && equipArmor.GetName() != "")
	{
		cout << equipArmor.GetName() << " ����!" << endl;
		player->SetDEF(player->GetDEF() - equipArmor.GetEffPoint());
		invenItems.push_back(equipArmor);
		equipArmor = Item();
	}
	else if (index == 2 && equipWeapon.GetName() != "")
	{
		cout << equipWeapon.GetName() << " ����!" << endl;
		player->SetATK(player->GetATK() - equipWeapon.GetEffPoint());
		invenItems.push_back(equipWeapon);
		equipWeapon = Item();
	}
	else if (index == 3 && equipRing.GetName() != "")
	{
		cout << equipRing.GetName() << " ����!" << endl;
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
		cout << "������ �������� �����ϴ�." << endl;
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
		cout << "�÷��̾��� ü���� " << invenItems[index].GetEffPoint() << " ��ŭ ȸ���մϴ�." << endl;
		Sleep(900);
		player->SetHP(player->GetHP() + invenItems[index].GetEffPoint());
	}
	else if (invenItems[index].GetEffect() == Effect::MP)
	{
		cout << "�÷��̾��� ������ " << invenItems[index].GetEffPoint() << " ��ŭ ȸ���մϴ�." << endl;
		Sleep(900);
		player->SetMP(player->GetMP() + invenItems[index].GetEffPoint());
	}
	else if (invenItems[index].GetEffect() == Effect::ATK)
	{
		cout << "�÷��̾��� ���ݷ��� " << invenItems[index].GetEffPoint() << " ��ŭ �����մϴ�." << endl;
		Sleep(900);
		player->SetATK(player->GetATK() + invenItems[index].GetEffPoint());
	}
	else
	{

	}

	invenItems.erase(invenItems.begin() + index);

}
