#include "MapGenerator.h"

int main()
{
	MapGenerator* m = new MapGenerator();
	m->GenerateBSP();
	//����, �÷��̾� ��ġ �˸��� ������ �ʱ�ȭ.
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