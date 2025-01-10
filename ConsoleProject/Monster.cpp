#include "Monster.h"
#include <Windows.h>

Monster::Monster(const int money, const string& name)
	:m_money(money), m_name(name)
{
}

void Monster::Attack(Player& player)
{
	cout << m_name<<" 이(가) "<<player.GetName() << " 을 공격합니다." << endl;
	Sleep(800);
	int pHP = player.GetHP() + (int(player.GetDEF() / 2));
	pHP -= m_ATK;
	player.SetHP(pHP);
	cout << player.GetName() << "에게 " << m_ATK << " 만큼 피해를 입혔습니다.." << endl;
	Sleep(1000);
}

void Monster::Skill(Player& player)
{
}

void Monster::Dead()
{
	cout << m_name << " 이 쓰러졌습니다!" << endl;
	sc->PlayVictoryBGM();
	Sleep(500);
	cout << m_money << "원을 획득하셨습니다." << endl;
	m_life = false;
	_getch();
}

int Monster::DropItem()
{
	return m_money;
}
