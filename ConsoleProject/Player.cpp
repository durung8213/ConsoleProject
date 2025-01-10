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
	cout << "================= �÷��̾� ���� =================" << endl;
	cout << m_name << "�� ü�� : " << this->m_HP << endl;
	cout << m_name << "�� ���� : " << this->m_MP << endl;
	cout << m_name << "�� ���ݷ� : " << this->m_ATK << endl;
	cout << m_name << "�� ���� : " << this->m_DEF << endl;
	cout << m_name << "�� ������ : " << this->m_Inven.GetGill() <<"��"<< endl;
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
	cout << m->GetName() << " �� �����մϴ�." << endl;
	Sleep(1500);
	cout << m->GetName() << "���� " << this->GetATK() << "��ŭ ������!" << endl;
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
				cout << "��ų "<< pair.first <<"�� �����մϴ�!" << endl;
				Sleep(1000);
				damage = m_ATK + pair.second;
				targetHP -= damage;
				cout << m->GetName() << " ���� " << damage << "�� �������� �������ϴ�!" << endl;
				Sleep(1000);
				m->SetHP(targetHP);
				return true;
			}
			else
			{
				cout << "������ �����մϴ�!" << endl;
				Sleep(800);
				return false;
			}
			
		}
		else if (pair.first == sk && sk == "CURE")
		{
			if (m_MP >= pair.second)
			{
				m_MP -= pair.second;
				cout << "��ų "<<pair.first<<"�� �����մϴ�!" << endl;
				Sleep(1000);
				this->SetHP(this->GetHP() + pair.second);
				cout << this->GetName() << " �� ü���� " << pair.second << "��ŭ ȸ���մϴ�." << endl;
				Sleep(1000);
				return true;
			}
			else
			{
				cout << "������ �����մϴ�!" << endl;
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
		cout << "==== �κ��丮�� ����ֽ��ϴ�. ====" << endl;
		Sleep(900);
		return;
	}
	else
	{
		cout << "����� �������� ���ڸ� �Է��ϼ���." << endl;
		cout << "							9 : �ڷΰ���" << endl;
		int num;
		cin >> num;

		if (num == 9)
			return;

		m_Inven.UseItem(num - 1);
	}
}


