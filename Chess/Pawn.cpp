#include "ChessMan.h"
#include "Position.h"
#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(int C, Position position) : ChessMan(C, position)
{
	this->color = C;
	this->position = position;
}

bool Pawn::Move(Position newPosition, Board mainBoard)
{
	if (newPosition == position || mainBoard.getChess(newPosition)->color == this->color)
	{
		return false;
	}
	if (newPosition.x < 0 || newPosition.x > 7 || newPosition.y < 0 || newPosition.y > 7)
	{
		return false;
	}
	Position left = Position(position.x - 1, position.y);
	Position right = Position(position.x + 1, position.y);
	ChessMan* chessLeft = mainBoard.getChess(left);
	ChessMan* chessRight = mainBoard.getChess(right);
	if (chessLeft != nullptr)
	{
		if (chessLeft->color == ~this->color)
		{
			mainBoard.EatChess(left);
			if (this->color = black)
			{
				if (newPosition == Position(position.x - 1, position.y - 1))
				{
					return true;
				}
			}
			else
			{
				if (newPosition == Position(position.x - 1, position.y + 1))
				{
					return true;
				}
			}
		}
	}
	else if (chessRight != nullptr)
	{
		if (chessRight->color == ~this->color)
		{
			mainBoard.EatChess(right);
			if (this->color = black)
			{
				if (newPosition == Position(position.x + 1, position.y - 1))
				{
					return true;
				}
			}
			else
			{
				if (newPosition == Position(position.x + 1, position.y + 1))
				{
					return true;
				}
			}
		}
	}
	else if (this->step == 0)
	{
		if (this->color == black)
		{
			if (newPosition == Position(position.x, position.y - 1 || position.y - 2))
			{
				return true;
			}
		}
		else
		{
			if (newPosition == Position(position.x, position.y + 1 || position.y + 2))
			{
				return true;
			}
		}
	}
	else if (this->step != 0)
	{
		if (this->color == black)
		{
			if (newPosition == Position(position.x, position.y - 1))
			{
				ChessMan* chess = mainBoard.getChess(newPosition);
				if (chess != nullptr)
				{
					mainBoard.EatChess(newPosition);
				}
				if (newPosition.y == 0)
				{
					mainBoard.Promotion(newPosition);
				}
				return true;
			}
		}
		else
		{
			if (newPosition == Position(position.x, position.y + 1))
			{
				ChessMan* chess = mainBoard.getChess(newPosition);
				if (chess != nullptr)
				{
					mainBoard.EatChess(newPosition);
				}
				if (newPosition.y == 7)
				{
					mainBoard.Promotion(newPosition);
				}
				return true;
			}
		}
	}
	return false;
}
