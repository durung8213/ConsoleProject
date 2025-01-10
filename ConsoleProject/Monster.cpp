#include "Monster.h"
#include <Windows.h>

Monster::Monster(const int money, const string& name)
	:m_money(money), m_name(name)
{
}

void Monster::Attack(Player& player)
{
	cout << m_name<<" ��(��) "<<player.GetName() << " �� �����մϴ�." << endl;
	Sleep(800);
	int pHP = player.GetHP() + (int(player.GetDEF() / 2));
	pHP -= m_ATK;
	player.SetHP(pHP);
	cout << player.GetName() << "���� " << m_ATK << " ��ŭ ���ظ� �������ϴ�.." << endl;
	Sleep(1000);
}

void Monster::Skill(Player& player)
{
}

void Monster::Dead()
{
	cout << m_name << " �� ���������ϴ�!" << endl;
	sc->PlayVictoryBGM();
	Sleep(500);
	cout << m_money << "���� ȹ���ϼ̽��ϴ�." << endl;
	m_life = false;
	_getch();
}

int Monster::DropItem()
{
	return m_money;
}
