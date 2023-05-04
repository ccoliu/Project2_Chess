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
	if (this->color == white)
	{
		if (this->step == 0)
		{
			if (newPosition == Position(position.x, position.y + 1) || newPosition == Position(position.x, position.y + 2))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			ChessMan* UpperLeftChess = mainBoard.getChess(Position(position.x - 1, position.y + 1));
			ChessMan* UpperRightChess = mainBoard.getChess(Position(position.x + 1, position.y + 1));
			ChessMan* LeftChess = mainBoard.getChess(Position(position.x - 1, position.y));
			ChessMan* RightChess = mainBoard.getChess(Position(position.x + 1, position.y));
			if (newPosition == Position(position.x - 1, position.y + 1))
			{
				if (UpperLeftChess != nullptr && UpperLeftChess->color != this->color)
				{
					mainBoard.EatChess(Position(position.x - 1, position.y + 1));
					return true;
				}
				else if (LeftChess != nullptr && LeftChess->color != this->color && typeid(*LeftChess) == typeid(Pawn) && LeftChess->step == 1)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y));
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (newPosition == Position(position.x + 1, position.y + 1))
			{
				if (UpperRightChess != nullptr && UpperRightChess->color != this->color)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y + 1));
					return true;
				}
				else if (RightChess != nullptr && RightChess->color != this->color && typeid(*RightChess) == typeid(Pawn) && RightChess->step == 1)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y));
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (newPosition == Position(position.x, position.y + 1))
			{
				if (position.y + 1 == 7)
				{
					mainBoard.Promotion(Position(position.x, position.y + 1));
				}
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (this->step == 0)
		{
			if (newPosition == Position(position.x, position.y - 1) || newPosition == Position(position.x, position.y - 2))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			ChessMan* LowerLeftChess = mainBoard.getChess(Position(position.x - 1, position.y - 1));
			ChessMan* LowerRightChess = mainBoard.getChess(Position(position.x + 1, position.y - 1));
			ChessMan* LeftChess = mainBoard.getChess(Position(position.x - 1, position.y));
			ChessMan* RightChess = mainBoard.getChess(Position(position.x + 1, position.y));
			if (newPosition == Position(position.x - 1, position.y - 1))
			{
				if (LowerLeftChess != nullptr && LowerLeftChess->color != this->color)
				{
					mainBoard.EatChess(Position(position.x - 1, position.y - 1));
					return true;
				}
				else if (LeftChess != nullptr && LeftChess->color != this->color && typeid(*LeftChess) == typeid(Pawn) && LeftChess->step == 1)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y));
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (newPosition == Position(position.x + 1, position.y - 1))
			{
				if (LowerRightChess != nullptr && LowerRightChess->color != this->color)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y - 1));
					return true;
				}
				else if (RightChess != nullptr && RightChess->color != this->color && typeid(*RightChess) == typeid(Pawn) && RightChess->step == 1)
				{
					mainBoard.EatChess(Position(position.x + 1, position.y));
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (newPosition == Position(position.x, position.y - 1))
			{
				if (position.y - 1 == 0)
				{
					mainBoard.Promotion(Position(position.x, position.y - 1));
				}
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
