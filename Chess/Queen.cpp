//File : Queen.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include "Queen.h"
//constructure
Queen::Queen(Color col, Position position) : ChessMan(col, position)
{
	//set two icon of white and black
	if (col == Color::white)
	{
		this->icon = 'q';
	}
	else
	{
		this->icon = 'Q';
	}
};
//return the normal condition where Queen can move
vector<Position> Queen::Move(Position newPosition)
{
	vector<Position> accessable;
	for (int i = 0; i < 7; i++)
	{
		accessable.push_back(Position(position.y + i, position.x));
		accessable.push_back(Position(position.y - i, position.x));
		accessable.push_back(Position(position.y, position.x + i));
		accessable.push_back(Position(position.y, position.x - i));
		accessable.push_back(Position(position.y + i, position.x + i));
		accessable.push_back(Position(position.y + i, position.x - i));
		accessable.push_back(Position(position.y - i, position.x + i));
		accessable.push_back(Position(position.y - i, position.x - i));
	}
	return accessable;
}