#include "MapGenerator.h"

int main()
{
	MapGenerator* m = new MapGenerator();
	m->GenerateBSP();
	//상점, 플레이어 위치 알맞은 곳으로 초기화.
	m->GetIsSafe();
	while (true)
	{
		m->ClearMap();
		m->SetPlayer();
		m->PrintMap();

		if (_kbhit())
		{
			char input = _getch();
			m->movePtr->MovePlayer(m, m->p_Pos.x, m->p_Pos.y,input);
		}
	}

}