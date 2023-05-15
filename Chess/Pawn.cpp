//File : Pawn.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include "Pawn.h"
//constructure
Pawn::Pawn(Color col, Position position) : ChessMan(col, position)
{
	//set two icon of white and black
	if (col == Color::white)
	{
		this->icon = 'p';
	}
	else
	{
		this->icon = 'P';
	}
};
//return the normal condition where Pawn can move
vector<Position> Pawn::Move(Position newPosition)
{
	if (this->color == Color::black)
	{
		//if fist step to move Pawn can move two 
		if (this->step == 0)
		{
			vector<Position> possibleMove = { Position(position.y + 1, position.x), Position(position.y + 2, position.x),
											  Position(position.y + 1, position.x - 1), Position(position.y + 1, position.x + 1)};
			return possibleMove;
		}
		else
		{
			vector<Position> possibleMove = { Position(position.y + 1, position.x), Position(position.y + 1, position.x - 1),
														  Position(position.y + 1, position.x + 1) };
			return possibleMove;
		}
	}
	else
	{
		//if fist step to move Pawn can move two 
		if (this->step == 0)
		{
			vector<Position> possibleMove = { Position(position.y - 1, position.x), Position(position.y - 2, position.x),
														Position(position.y - 1, position.x - 1), Position(position.y - 1, position.x + 1) };
			return possibleMove;
		}
		else
		{
			vector<Position> possibleMove = { Position(position.y - 1, position.x), Position(position.y - 1, position.x - 1),
														  Position(position.y - 1, position.x + 1) };
			return possibleMove;
		}
	}
}