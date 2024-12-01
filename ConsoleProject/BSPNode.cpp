#include "BSPNode.h"

BSPNode::BSPNode(int x, int y, int w, int h)
	:_x(x), _y(y), _w(w), _h(h)
{
	
}

void BSPNode::GetRoom(OUT vector<Room*>& rooms)
{
	//만약 두 방향의 자식이 아무것도 가르키지 않고,  방이 있다면 (마지막 노드의 방이라면)
	if (!_LChild && !_RChild && _room)
	{
		//그 방을 rooms vector에 집어 넣는다. 
		rooms.push_back(_room);
	}
	else
	{
		if (_LChild)
		{
			_LChild->GetRoom(rooms);
		}
		if (_RChild)
		{
			_RChild->GetRoom(rooms);	
		}
	}
}

void BSPNode::GetBSPNode(OUT vector<BSPNode*>& bspNode)
{
	bspNode.push_back(this);
	if (_LChild)
	{
		_LChild->GetBSPNode(bspNode);
	}
	if (_RChild)
	{
		_RChild->GetBSPNode(bspNode);
	}
}

BSPNode* BSPNode::CreateBSPNode(int x, int y, int w, int h)
{
	BSPNode* bspNode = new BSPNode(x, y, w, h);
	return bspNode;
}

int BSPNode::GetRandomNum(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int>dis(min, max);

	return dis(gen);
}



void BSPNode::BSP()
{
	memset(map, 0, sizeof(map));
	BSPNode* root = CreateBSPNode(0, 0, mapSizeX, mapSizeY);
	Divide(root);
	Connect(root);

	vector<Room*> rooms;
	root->GetRoom(rooms);

	for (auto item : rooms)
	{
		int x = item->_x;
		int y = item->_y;
		int w = item->_w;
		int h = item->_h;
		
		for (int i = y; i < y + h; i++)
		{
			for (int k = x; k < x + w; k++)
			{
				map[i][k] = 1;
			}
		}

	
	}
}


void BSPNode::Divide(BSPNode* parent)
{
	int xLen = parent->_w;
	int yLen = parent->_h;

	int x = parent->_x;
	int y = parent->_y;
	int w = parent->_w;
	int h = parent->_h;

	int ratio = GetRandomNum(4, 6);

	if (w - 4 <= minX || h - 4 <= minY)
	{
		Room* room = MakeRoom(parent);
		return;
	}

	if (xLen > yLen)
	{
		int slicedW = w * ratio / 10;

		//LChild
		BSPNode* LChild = CreateBSPNode(x, y, slicedW, h);

		//RChild
		BSPNode* RChild = CreateBSPNode(x + slicedW, y, w - slicedW, h);


		//Recursive
		Divide(LChild);
		Divide(RChild);

		parent->_LChild = LChild;
		parent->_RChild = RChild;
	}

	else if (xLen <= yLen)
	{
		int slicedH = h * ratio / 10;

		//LChild
		BSPNode* LChild = CreateBSPNode(x, y, w, slicedH);

		//RChild
		BSPNode* RChild = CreateBSPNode(x, y + slicedH, w, h - slicedH);

		//Recursive
		Divide(LChild);
		Divide(RChild);

		parent->_LChild = LChild;
		parent->_RChild = RChild;
	}	


}

void BSPNode::Connect(BSPNode* root)
{
	//자식이 없을 경우, 즉 분할이 한번이라도 되지 않았을 경우 연결 불가능
	if (root->_LChild == nullptr || root->_RChild == nullptr)
	{
		return;
	}

	Point LCenter = root->_LChild->GetCenter();
	Point RCenter = root->_RChild->GetCenter();

	Road* road = new Road(LCenter.x,LCenter.y,RCenter.x,RCenter.y);
	root->_road = road;

	//연결하려고 하는 방의 두 중심점의 x축이 같다면
	if (LCenter.x == RCenter.x) 
	{
		//가로가 평행하기때문에 세로로 길을 만들어준다.
		for (int i = LCenter.y; i < RCenter.y; i++)
		{
			//길을 이어준다.
			map[i][LCenter.x] = 2;
		}
	}
	//연결하려고 하는 방의 두 중심점의 y축이 같다면
	else if (LCenter.y == RCenter.y)
	{
		//세로로 평행하기 때문에 가로로 길을 만들어준다.
		for (int i = LCenter.x; i < RCenter.x; i++)
		{
			map[LCenter.y][i] = 2;
		}
	}

	Connect(root->_LChild);
	Connect(root->_RChild);

}

Room* BSPNode::MakeRoom(BSPNode* bspNode)
{
	int x = bspNode->_x;
	int y = bspNode->_y;
	int w = bspNode->_w;
	int h = bspNode->_h;

	Room* room = new Room();

	room->_x = x + 1;
	room->_y = y + 1;
	room->_w = w - 2;
	room->_h = h - 2;

	bspNode->_room = room;
	return room;
}
