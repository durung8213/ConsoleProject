#include "MapController.h"


MapController::MapController()
{
	//처음만 실행
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

	//더블 버퍼 시도 -> 색상 출현이 어려워 실패
	/*buffer->ScreenPrint(0, 0, map->mapPtr->mapDraw);
	buffer->ScreenFlipping();
	buffer->ScreenClear();*/
}

