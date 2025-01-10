#include "MoveController.h"
#include "MapGenerator.h"
#include "GameManager.h"

void MoveController::MovePlayer(MapGenerator* mPtr, int& px, int& py, char input)
{
	IsShop = false;
	switch (input)
	{
	case 'w':
		if (py > 0 && mPtr->bsp->map[py - 1][px] != 0)
		{
			py--;
			SaveLastPos(mPtr, px, py);
		}
		break;
	case 's':
		if (py < mapSizeY - 1 && mPtr->bsp->map[py + 1][px] != 0)
		{
			py++;
			SaveLastPos(mPtr, px, py);
		}
		break;
	case 'a':
		if (px > 0 && mPtr->bsp->map[py][px - 1] != 0)
		{
			px--;
			SaveLastPos(mPtr, px, py);
		}
		break;
	case 'd':
		if (px < mapSizeX - 1 && mPtr->bsp->map[py][px + 1] != 0)
		{
			px++;
			//�̵��Ϸ��� �ϴ� ���� ���� ���¸� �����ص�.
			SaveLastPos(mPtr, px, py);
		}
		break;
	case 'm':
		// Ű���� m �� ���� ���, �ʱ�ȭ������ ���ư��� �ǰ�, ������ ������ �� �ִ�.
		GoStart = true;
		break;
	default:
		break;
	}
	DetactObject(mPtr, px, py);
}


void MoveController::SaveLastPos(MapGenerator* mPtr, int& px, int& py)
{
	mPtr->UpdatePos();
	mPtr->lastX = px;
	mPtr->lastY = py;
	mPtr->lastInfo = mPtr->bsp->map[py][px];
}

void MoveController::DetactObject(MapGenerator* mPtr, int& px, int& py)
{
	if (mPtr->bsp->map[py][px] == 4)
	{
		//���� player�� �̵��� ������ �����̶��
		IsShop = true;
		return;
	}
	// �ʷϻ� ���� ���� ��, Ȯ�������� ���Ͱ� ��Ÿ������ �Ѵ�.
	else if (mPtr->bsp->map[py][px] == 1 && mPtr->IsBattleStart())
	{
		IsBattle = true;
		return;
	}
}


