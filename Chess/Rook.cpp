//File : Rook.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include "Rook.h"

Rook::Rook(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'r';
	}
	else
	{
		this->icon = 'R';
	}
};
vector<Position> Rook::Move(Position newPosition)
{
	vector<Position> accessable;
	for (int i = 1; i < 8; i++)
	{
		accessable.push_back(Position(position.y + i, position.x));
		accessable.push_back(Position(position.y - i, position.x));
		accessable.push_back(Position(position.y, position.x + i));
		accessable.push_back(Position(position.y, position.x - i));
	}
	return accessable;
}