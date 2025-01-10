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
			//이동하려고 하는 곳의 지역 상태를 저장해둠.
			SaveLastPos(mPtr, px, py);
		}
		break;
	case 'm':
		// 키보드 m 을 누를 경우, 초기화면으로 돌아가게 되고, 게임을 종료할 수 있다.
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
		//현재 player가 이동한 공간이 상점이라면
		IsShop = true;
		return;
	}
	// 초록색 길을 걸을 때, 확률적으로 몬스터가 나타나도록 한다.
	else if (mPtr->bsp->map[py][px] == 1 && mPtr->IsBattleStart())
	{
		IsBattle = true;
		return;
	}
}


