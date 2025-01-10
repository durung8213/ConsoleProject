#include "GameManager.h"

void GameManager::StartGame()
{
	InitConsole();
	while (true)
	{
		scene->ShowCurrentScene();
		scene->UpdataScene();

		if (scene->startPtr->GameOver)
			return;
	}

}

void GameManager::InitConsole()
{
	system("mode con:cols=95 lines=50 | title ConSole FANTASY");
	CONSOLE_CURSOR_INFO cur;
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	return;
}

void GameManager::ChangeScene(const string& name)
{
	scene->SetCurrentScene(name);
}
