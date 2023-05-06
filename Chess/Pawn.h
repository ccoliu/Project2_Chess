#pragma once
#include "ChessMan.h"
#include "Board.h"

class Pawn : public ChessMan
{
	public:
	Pawn(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'P';
		}
		else
		{
			this->icon = 'p';
		}
	};
	vector<Position> Move(Position newPosition) override
	{
		if (this->color == Color::black)
		{
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
};