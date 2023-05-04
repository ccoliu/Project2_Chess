#pragma once
#include "Position.h"
#include "ChessMan.h"

class Knight : public ChessMan
{
	public:
	Knight(int C, Position position);
	bool Move(Position newPosition, Board mainBoard);
};
