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
	string GetName();
	string GetDesc();
	ItemType GetType();
	int GetPrice();
	int GetCount();
	int GetEffPoint();
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

