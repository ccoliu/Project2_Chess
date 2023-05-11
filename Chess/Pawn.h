#pragma once
#include "ChessMan.h"
#include "Board.h"

class Pawn : public ChessMan
{
	public:
		Pawn(Color col, Position position);
		vector<Position> Move(Position newPosition) override;
};