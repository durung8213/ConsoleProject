#include "Item.h"

Item::Item(ItemType type, const string& name, const string& description, Effect effect, int effectPoint, int price, int count)
{
}

string Item::GetName()
{
	return m_name;
}

string Item::GetDesc()
{
	return m_desc;
}

ItemType Item::GetType()
{
	return m_type;
}

int Item::GetPrice()
{
	return m_price;
}

int Item::GetCount()
{
	return m_count;
}

int Item::GetEffPoint()
{
	return m_effectPoint;
}

void Item::SetCount(int count)
{
	m_count = count;
}
