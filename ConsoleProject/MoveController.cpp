#include "MoveController.h"
#include "MapGenerator.h"

void MoveController::MovePlayer(MapGenerator* mPtr, int& px, int& py, char input)
{
	switch (input)
	{
	case 'w':
		if (py > 0 && mPtr->bsp->map[py - 1][px] != 0)
		{
			SaveLastPos(mPtr, px, py);
			py--;
			SaveLastInfo(mPtr, px, py);
		}
		break;
	case 's':
		if (py < mapSizeY - 1 && mPtr->bsp->map[py + 1][px] != 0)
		{
			SaveLastPos(mPtr, px, py);
			py++;
			SaveLastInfo(mPtr, px, py);
		}
		break;
	case 'a':
		if (px > 0 && mPtr->bsp->map[py][px - 1] != 0)
		{
			SaveLastPos(mPtr, px, py);
			px--;
			SaveLastInfo(mPtr, px, py);
		}
		break;
	case 'd':
		if (px < mapSizeX - 1 && mPtr->bsp->map[py][px + 1] != 0)
		{
			SaveLastPos(mPtr, px, py);
			px++;
			SaveLastInfo(mPtr, px, py);
		}
		break;
	default:
		break;
	}
}
//문제 해결 해야함.
void MoveController::SaveLastPos(MapGenerator* mPtr, int& px, int& py)
{
	mPtr->lastX = px;
	mPtr->lastY = py;
}

void MoveController::SaveLastInfo(MapGenerator* mPtr, int& px, int& py)
{
	mPtr->lastInfo = mPtr->bsp->map[py][px];
	mPtr->UpdatePos();
}

