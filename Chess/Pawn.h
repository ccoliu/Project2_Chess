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
	bool Move(Position newPosition, Board mainBoard) override
	{
		if (newPosition == position)
		{
			return false;
		}
		if (mainBoard.getChess(newPosition) != nullptr && mainBoard.getChess(newPosition)->getColor() == this->color)
		{
			return false;
		}
		if (newPosition.x < 0 || newPosition.x > 7 || newPosition.y < 0 || newPosition.y > 7)
		{
			return false;
		}
		if (this->color == Color::black)
		{
			if (this->step == 0)
			{
				if (newPosition == Position(position.y + 1, position.x) || newPosition == Position(position.y + 2, position.x))
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
				ChessMan* UpperLeftChess = mainBoard.getChess(Position(position.y + 1, position.x - 1));
				ChessMan* UpperRightChess = mainBoard.getChess(Position(position.y + 1, position.x + 1));
				ChessMan* LeftChess = mainBoard.getChess(Position(position.y, position.x - 1));
				ChessMan* RightChess = mainBoard.getChess(Position(position.y, position.x + 1));
				if (newPosition == Position(position.y + 1, position.y - 1))
				{
					if (UpperLeftChess != nullptr && UpperLeftChess->getColor() != this->color)
					{
						mainBoard.EatChess(Position(position.y + 1, position.x - 1));
						return true;
					}
					else if (LeftChess != nullptr && LeftChess->getColor() != this->color && typeid(*LeftChess) == typeid(Pawn) && LeftChess->getStep() == 1)
					{
						mainBoard.EatChess(Position(position.y, position.x + 1));
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (newPosition == Position(position.y + 1, position.x + 1))
				{
					if (UpperRightChess != nullptr && UpperRightChess->getColor() != this->color)
					{
						mainBoard.EatChess(Position(position.y + 1, position.x + 1));
						return true;
					}
					else if (RightChess != nullptr && RightChess->getColor() != this->color && typeid(*RightChess) == typeid(Pawn) && RightChess->getStep() == 1)
					{
						mainBoard.EatChess(Position(position.y, position.x + 1));
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (newPosition == Position(position.y + 1, position.x))
				{
					if (position.y + 1 == 7)
					{
						mainBoard.Promotion(Position(position.y + 1, position.x));
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
				if (newPosition == Position(position.y - 1, position.x) || newPosition == Position(position.y - 2, position.x))
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
				ChessMan* LowerLeftChess = mainBoard.getChess(Position(position.y - 1, position.x - 1));
				ChessMan* LowerRightChess = mainBoard.getChess(Position(position.y - 1, position.x + 1));
				ChessMan* LeftChess = mainBoard.getChess(Position(position.y, position.x - 1));
				ChessMan* RightChess = mainBoard.getChess(Position(position.y, position.x + 1));
				if (newPosition == Position(position.y - 1, position.x - 1))
				{
					if (LowerLeftChess != nullptr && LowerLeftChess->getColor() != this->color)
					{
						mainBoard.EatChess(Position(position.y - 1, position.x - 1));
						return true;
					}
					else if (LeftChess != nullptr && LeftChess->getColor() != this->color && typeid(*LeftChess) == typeid(Pawn) && LeftChess->getStep() == 1)
					{
						mainBoard.EatChess(Position(position.y, position.x + 1));
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (newPosition == Position(position.y - 1, position.x + 1))
				{
					if (LowerRightChess != nullptr && LowerRightChess->getColor() != this->color)
					{
						mainBoard.EatChess(Position(position.y - 1, position.x + 1));
						return true;
					}
					else if (RightChess != nullptr && RightChess->getColor() != this->color && typeid(*RightChess) == typeid(Pawn) && RightChess->getStep() == 1)
					{
						mainBoard.EatChess(Position(position.y, position.x + 1));
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (newPosition == Position(position.y - 1, position.x))
				{
					if (position.y - 1 == 0)
					{
						mainBoard.Promotion(Position(position.y - 1, position.x));
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
};