#include <vector>
#include "Position.h"
#include "ChessMan.h"
#include "Board.h"
#include "Knight.h"

Knight::Knight(int C, Position position) : ChessMan(C, position)
{
	this->color = C;
	this->position = position;
}

bool Knight::Move(Position newPosition, Board mainBoard)
{
	if (newPosition == position || mainBoard.getChess(newPosition)->color == this->color)
	{
		return false;
	}
	if (newPosition.x < 0 || newPosition.x > 7 || newPosition.y < 0 || newPosition.y > 7)
	{
		return false;
	}
	vector<Position> accessable = {{position.x - 2, position.y - 1}, {position.x - 2, position.y + 1},
								   {position.x - 1, position.y - 2}, {position.x - 1, position.y + 2},
								   {position.x + 1, position.y - 2}, {position.x + 1, position.y + 2}, 
								   {position.x + 2, position.y - 1}, {position.x + 2, position.y + 1}};
	if (find(accessable.begin(), accessable.end(), newPosition) != accessable.end())
	{
		if (mainBoard.getChess(newPosition) == nullptr)
		{
			return true;
		}
		else if (mainBoard.getChess(newPosition)->color != this->color)
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