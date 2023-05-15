//File : Bishop.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/15
//Description:Chess

#include "Bishop.h"

//Bishop constructure
Bishop::Bishop(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'b';
	}
	else
	{
		this->icon = 'B';
	}
};
//return the Bishop valid move
vector<Position> Bishop::Move(Position newPosition)
{
	vector<Position> accessable;
	for (int i = 0; i < 7; i++)
	{
		accessable.push_back(Position(position.y + i, position.x + i));
		accessable.push_back(Position(position.y + i, position.x - i));
		accessable.push_back(Position(position.y - i, position.x + i));
		accessable.push_back(Position(position.y - i, position.x - i));
	}
	return accessable;
}