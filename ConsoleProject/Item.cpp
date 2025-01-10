#include "Item.h"

Item::Item(ItemType type, const string& name, const string& description, Effect effect, int effectPoint, int price, int count)
	:m_type(type), m_name(name), m_desc(description), m_effect(effect), m_effectPoint(effectPoint),
	m_price(price), m_count(count)
{
}

string Item::GetName() const
{
	return m_name;
}

string Item::GetDesc() const
{
	return m_desc;
}

ItemType Item::GetType() const
{
	return m_type;
}

Effect Item::GetEffect() const
{
	return m_effect;
}

int Item::GetPrice() const
{
	return m_price;
}

int Item::GetCount() const
{
	return m_count;
}

int Item::GetEffPoint() const
{
	return m_effectPoint;
}

void Item::SetCount(int count)
{
	m_count = count;
}
