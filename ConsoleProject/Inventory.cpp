#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{
}

void Inventory::ShowInventory() const
{

}

void Inventory::AddItem(const Item& item)
{
	items.push_back(item);
}

Item Inventory::SellItem(const int index, int& price)
{
	if (items.empty())
	{
		cout << "인벤토리가 비어있습니다." << endl;
		return Item();
	}

}

void Inventory::EquipItem(const int index)
{
	Item equip = items[index - 1];
	cout << equip.GetName() << " 장착!" << endl;
	switch (equip.GetType())
	{
	case ItemType::ITEM_ARMOR:
		equipArmor = equip;
		break;
	case ItemType::ITEM_WEAPON:
		equipWeapon = equip;
		break;
	case ItemType::ITEM_RING:
		equipRing = equip;
		break;
	default:
		break;
	}
	items.erase(items.begin() + index);
}

void Inventory::EquipOff(const Item& item)
{

}

Item Inventory::GetEquippedArmor() const
{
	return equipArmor;
}

Item Inventory::GetEquippedWeapon() const
{
	return equipWeapon;
}

Item Inventory::GetEquippedRing() const
{
	return equipRing;
}
