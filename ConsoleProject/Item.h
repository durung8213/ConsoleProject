#pragma once
#include"GameEnums.h"
#include<iostream>
#include<string>

using namespace std;
using namespace GameEnums;

class Item
{

public:
	Item() {}
	Item(ItemType type, const string& name, const string& description, Effect effect,
		int effectPoint, int price, int count);

	string GetName() const;
	string GetDesc() const;
	ItemType GetType() const;
	Effect GetEffect() const;
	int GetPrice() const;
	int GetCount() const;
	int GetEffPoint() const;
	void SetCount(int count);

private:
	string m_name;
	string m_desc;
	Effect m_effect;
	ItemType m_type;
	int m_effectPoint;
	int m_count;
	int m_price;


};

