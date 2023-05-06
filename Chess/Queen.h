#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Rook : public ChessMan
{
public:
	//initialize the queen
	Rook(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'Q';
		}
		else
		{
			this->icon = 'q';
		}
	};
	//check whether the new position can move
	bool Move(Position newPosition, Board mainBoard) override
	{
		if (newPosition == position || (mainBoard.getChess(newPosition) != nullptr && mainBoard.getChess(newPosition)->getColor() == this->color))
		{
			return false;
		}
		if (newPosition.x < 0 || newPosition.x > 7 || newPosition.y < 0 || newPosition.y > 7)
		{
			return false;
		}
		if (abs(newPosition.x - this->position.x)  != abs(newPosition.y - this->position.y) )
		{
			return false;
		}
		if (newPosition.x - this->position.x > 0)
		{
			if (mainBoard.getChess(newPosition) == nullptr)
			{
				return true;
			}
			else if (mainBoard.getChess(newPosition)->getColor() != this->color)
			{
				mainBoard.EatChess(newPosition);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (newPosition.y - this->position.y != 0)
		{
			if (mainBoard.getChess(newPosition) == nullptr)
			{
				return true;
			}
			else if (mainBoard.getChess(newPosition)->getColor() != this->color)
			{
				mainBoard.EatChess(newPosition);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};
