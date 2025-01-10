#include "Player.h"
#include "Monster.h"
#include <Windows.h>
#include <conio.h>

Player::Player(const string& name, const Job job, const string& sk1, const string& sk2, const int hp,
	const int mp, const int atk, const int def, const double crt)
{
	m_name = name;
	m_job = job;
	m_Skill.insert(make_pair(sk1, 40));
	m_Skill.insert(make_pair(sk2, 30));
	m_HP = hp;
	m_MP = mp;
	m_ATK = atk;
	m_DEF = def;
	m_CRT = crt;

}

void Player::ShowStatus()
{
	cout << "================= 플레이어 정보 =================" << endl;
	cout << m_name << "의 체력 : " << this->m_HP << endl;
	cout << m_name << "의 마력 : " << this->m_MP << endl;
	cout << m_name << "의 공격력 : " << this->m_ATK << endl;
	cout << m_name << "의 방어력 : " << this->m_DEF << endl;
	cout << m_name << "의 소지금 : " << this->m_Inven.GetGill() <<"원"<< endl;
	this->m_Inven.ShowEquip();
	_getch();
}

void Player::ShowEquip() const
{
	m_Inven.ShowEquip();
}

Item Player::SellItem(const int itemNum)
{
	return m_Inven.SellItem(itemNum);
}

void Player::EquipItem(const int num)
{
	m_Inven.EquipItem(num,this);
}

void Player::EquipOffItem(const int num)
{
	m_Inven.EquipOff(num, this);
}

void Player::AddItemToInventory(const Item &item)
{
	m_Inven.AddItem(item);
}

void Player::ShowInventory() const
{
	m_Inven.ShowInventory();
}

void Player::Attack(Monster* m)
{
	int targetHP = m->GetHP();
	targetHP -= this->GetATK();
	cout << m->GetName() << " 을 공격합니다." << endl;
	Sleep(1500);
	cout << m->GetName() << "에게 " << this->GetATK() << "만큼 데미지!" << endl;
	Sleep(800);
	m->SetHP(targetHP);

}

bool Player::Skill(Monster* m, const string& sk)
{
	int targetHP = m->GetHP();
	int damage = 0;

	for (const auto& pair : m_Skill)
	{
		if (pair.first == sk && sk == "FIRE")
		{
			if (m_MP >= pair.second)
			{
				m_MP -= pair.second;
				cout << "스킬 "<< pair.first <<"를 시전합니다!" << endl;
				Sleep(1000);
				damage = m_ATK + pair.second;
				targetHP -= damage;
				cout << m->GetName() << " 에게 " << damage << "의 데미지를 입혔습니다!" << endl;
				Sleep(1000);
				m->SetHP(targetHP);
				return true;
			}
			else
			{
				cout << "마나가 부족합니다!" << endl;
				Sleep(800);
				return false;
			}
			
		}
		else if (pair.first == sk && sk == "CURE")
		{
			if (m_MP >= pair.second)
			{
				m_MP -= pair.second;
				cout << "스킬 "<<pair.first<<"을 시전합니다!" << endl;
				Sleep(1000);
				this->SetHP(this->GetHP() + pair.second);
				cout << this->GetName() << " 의 체력을 " << pair.second << "만큼 회복합니다." << endl;
				Sleep(1000);
				return true;
			}
			else
			{
				cout << "마나가 부족합니다!" << endl;
				Sleep(800);
				return false;
			}
		}
	}
	return false;

}

void Player::UseItem()
{
	m_Inven.ShowInventory();
	m_Inven.player = this;
	if (m_Inven.GetItemSize() == 0)
	{
		cout << "==== 인벤토리가 비어있습니다. ====" << endl;
		Sleep(900);
		return;
	}
	else
	{
		cout << "사용할 아이템의 숫자를 입력하세요." << endl;
		cout << "							9 : 뒤로가기" << endl;
		int num;
		cin >> num;

		if (num == 9)
			return;

		m_Inven.UseItem(num - 1);
	}
}


