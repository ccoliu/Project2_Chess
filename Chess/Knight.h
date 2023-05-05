#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Board;

class Knight : public ChessMan
{
	public:
	Knight(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'K';
		}
		else
		{
			this->icon = 'k';
		}
	};
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
		vector<Position> accessable = { {position.x - 2, position.y - 1}, {position.x - 2, position.y + 1},
						   {position.x - 1, position.y - 2}, {position.x - 1, position.y + 2},
						   {position.x + 1, position.y - 2}, {position.x + 1, position.y + 2},
						   {position.x + 2, position.y - 1}, {position.x + 2, position.y + 1} };
		for (int i = 0; i < accessable.size(); i++)
		{
			cout << accessable[i].x << " " << accessable[i].y << endl;
		}
		if (find(accessable.begin(), accessable.end(), newPosition) != accessable.end())
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
