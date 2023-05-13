//File : King.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include "King.h"
//constructure
King::King(Color col, Position position) : ChessMan(col, position)
{
	//set two icon of white and black
	if (col == Color::white)
	{
		this->icon = 'k';
	}
	else
	{
		this->icon = 'K';
	}
};
//return the normal condition where King can move
vector<Position> King::Move(Position newPosition)
{
	vector<Position> accessable;
	accessable.push_back(Position(position.y + 1, position.x + 1));
	accessable.push_back(Position(position.y + 1, position.x - 1));
	accessable.push_back(Position(position.y - 1, position.x + 1));
	accessable.push_back(Position(position.y - 1, position.x - 1));
	accessable.push_back(Position(position.y + 1, position.x));
	accessable.push_back(Position(position.y - 1, position.x));
	accessable.push_back(Position(position.y, position.x + 1));
	accessable.push_back(Position(position.y, position.x - 1));
	return accessable;
}