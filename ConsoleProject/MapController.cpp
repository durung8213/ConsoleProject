#include "MapController.h"


MapController::MapController()
{
	//ó���� ����
	map->consoleInit();
	map->GenerateBSP();
	map->GetIsSafe();
}

void MapController::ShowCurrentScene() const
{
	map->ClearMap();
	map->SetPlayer();
	map->PrintMap();

	if (_kbhit())
	{
		char input = _getch();
		map->movePtr->MovePlayer(map, map->p_Pos.x, map->p_Pos.y, input);
	}

	//���� ���� �õ� -> ���� ������ ����� ����
	/*buffer->ScreenPrint(0, 0, map->mapPtr->mapDraw);
	buffer->ScreenFlipping();
	buffer->ScreenClear();*/
}

