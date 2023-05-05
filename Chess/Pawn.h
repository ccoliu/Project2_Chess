#pragma once
#include "Position.h"
#include "ChessMan.h"

class Pawn : public ChessMan
{
public:
	Pawn(int C, Position position);
	bool Move(Position newPosition, Board mainBoard);
};