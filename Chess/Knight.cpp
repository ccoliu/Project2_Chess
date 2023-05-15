//File : Knight.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/15
//Description:Chess

#include "Knight.h"
//constructure
Knight::Knight(Color col, Position position) : ChessMan(col, position)
{
	//set two icon of white and black
	if (col == Color::white)
	{
		this->icon = 'n';
	}
	else
	{
		this->icon = 'N';
	}
};
//return the normal condition where Knight can move
vector<Position> Knight::Move(Position newPosition) 
{
	vector<Position> accessable = { {position.y - 1, position.x - 2}, {position.y + 1, position.x - 2},
					   {position.y - 2, position.x - 1}, {position.y + 2, position.x - 1},
					   {position.y - 2, position.x + 1}, {position.y + 2, position.x + 1},
					   {position.y - 1, position.x + 2}, {position.y + 1, position.x + 2} };
	return accessable;
}