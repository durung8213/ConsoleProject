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
		//시작 화면
		soundPtr->PlayMainBGM();
		startPtr->SelectMenu();
	}
	else if (currentSceneName == "MAP")
	{
		//맵 씬으로
		soundPtr->PlayMapBGM();
		mcPtr->ShowCurrentScene();
	}
	else if (currentSceneName == "SHOP")
	{
		//상점 씬으로
		soundPtr->PlayShopBGM();
		shopPtr->UpdateShop();
	}
	else if (currentSceneName == "BATTLE")
	{
		//배틀 씬으로
		soundPtr->PlayBattleBGM();
		batPtr->UpdateBattle();
	}
	else
	{
		cout << "잘못된 장소!!" << endl;
	}
}

void SceneManager::UpdataScene()
{
	//씬의 조건이 해당하면 씬을 바꿔준다.
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

