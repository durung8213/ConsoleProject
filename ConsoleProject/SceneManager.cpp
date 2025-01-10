#include "SceneManager.h"
#include "SoundController.h"

SceneManager::SceneManager()
{
	AddScene("MAP");
	AddScene("SHOP");
	AddScene("Battle");
	AddScene("START");
	AddScene("GAMEOVER");
	shopPtr->m_player = player;
	batPtr->m_player = player;
}

void SceneManager::AddScene(const string& name)
{
	scenes.push_back(name);
}

void SceneManager::RemoveScene(const string& name)
{
	for (const string& str : scenes)
	{
		int i = 0;
		if (str == name )
		{
			scenes.erase(scenes.begin() + i);
		}
		i++;
	}
}

void SceneManager::SetCurrentScene(const string& name)
{
	currentSceneName = name;
}

void SceneManager::ShowCurrentScene() const
{
	if (currentSceneName == "START")
	{
		//���� ȭ��
		soundPtr->PlayMainBGM();
		startPtr->SelectMenu();
	}
	else if (currentSceneName == "MAP")
	{
		//�� ������
		soundPtr->PlayMapBGM();
		mcPtr->ShowCurrentScene();
	}
	else if (currentSceneName == "SHOP")
	{
		//���� ������
		soundPtr->PlayShopBGM();
		shopPtr->UpdateShop();
	}
	else if (currentSceneName == "BATTLE")
	{
		//��Ʋ ������
		soundPtr->PlayBattleBGM();
		batPtr->UpdateBattle();
	}
	else
	{
		cout << "�߸��� ���!!" << endl;
	}
}

void SceneManager::UpdataScene()
{
	//���� ������ �ش��ϸ� ���� �ٲ��ش�.
	if (mcPtr->map->movePtr->IsShop)
	{
		this->SetCurrentScene("SHOP");
		mcPtr->map->movePtr->IsShop = false;
		system("cls");
	}
	else if (mcPtr->map->movePtr->IsBattle)
	{
		this->SetCurrentScene("BATTLE");
		batPtr->BattleInit();
		mcPtr->map->movePtr->IsBattle = false;
		system("cls");
	}
	else if (mcPtr->map->movePtr->GoStart)
	{
		this->SetCurrentScene("START");
		mcPtr->map->movePtr->GoStart = false;
		system("cls");
	}
	else if (shopPtr->IsOut)
	{
		this->SetCurrentScene("MAP");
		shopPtr->IsOut = false;
	}
	else if (batPtr->BattleOver)
	{
		this->SetCurrentScene("MAP");
		batPtr->BattleOver = false;
	}
	else if (startPtr->GameStart)
	{
		this->SetCurrentScene("MAP");
		startPtr->GameStart = false;
	}

	
}

