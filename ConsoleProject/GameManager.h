#pragma once
#include "SceneManager.h"
class GameManager

{
public:
	GameManager(){}
	~GameManager() {
		delete scene;
		scene = nullptr;
	}
	void StartGame();
	void InitConsole();
	void ChangeScene(const string& name);
public:
	SceneManager* scene = new SceneManager();
};

