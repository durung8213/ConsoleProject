#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"

class BattleManager
{
public:
	shared_ptr<Player> m_player;
	bool BattleOver = false;
	void UpdateBattle();
	BattleManager();
	~BattleManager(); 
	void BattleInit(); 


private:
	void BattleStartInfo();

	void DrawMenu(const vector<std::string>& options, int selectedIndex);
	void SelectMenu(); 
	void SetSkillMenu();
	void SetUseItemMenu();

	void AttackToMonster();
	void SkillToMonster(const string& skill);
	void UseInvenItem();
	void Exit();

	void AttackToPlayer();

	void CheckHP();
	void PrintBattleScene();

private:
	Monster* monster;
	vector<string> mainOptions =
	{
		"공격",
		"스킬",
		"아이템",
		"도망가기"
	};
	int selectedIndex = 0;
	bool IsAttack = false;
};

