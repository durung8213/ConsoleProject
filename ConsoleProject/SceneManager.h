#pragma once
#include<iostream>
#include<map>
#include "MapController.h"
#include "ShopGenerator.h"
#include "BattleManager.h"
#include "Player.h"
#include "StartScene.h"
#include "SoundController.h"

using namespace std;

class SceneManager
{
public:
	shared_ptr<Player> player{new Player("Èæ¸¶µµ»ç", Job::BLACKMAGE,"FIRE","CURE", 100, 60,
		46, 30, 0.7)};
	unique_ptr<StartScene>startPtr{ new StartScene() };
	unique_ptr<MapController>mcPtr{ new MapController() };
private:
	vector<string> scenes;
	string currentSceneName = "START";
	unique_ptr<ShopGenerator>shopPtr{ new ShopGenerator() };
	unique_ptr<BattleManager>batPtr{ new BattleManager() };
	unique_ptr<SoundController>soundPtr{ new SoundController() };

public:
	SceneManager();
	~SceneManager() { };

	void AddScene(const string& name);
	void RemoveScene(const string& name);
	void SetCurrentScene(const string& name);
	void ShowCurrentScene()const;
	void UpdataScene();

};