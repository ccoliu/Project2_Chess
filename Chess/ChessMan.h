#pragma once
#include "Position.h"
#include "Board.h"

enum color
{
	white = 0,
	black = 1
};

class ChessMan
{
protected:
	friend class Board;
	Position position;
	int step = 0;
public:
	int color;
	ChessMan(int C, Position position);
	virtual bool Move(Position newPosition, Board mainBoard);
};