#pragma once
#include "Board.h"
#include "Position.h"

class ChessMan
{
public:
	friend class Board;
	friend struct Position;
	enum class Color { white, black };

	ChessMan(Color col, Position position) : color(col), position(position) {};
	char getIcon() { return icon; };
	int getStep() { return step; };
	Color getColor() { return color; };
	virtual ~ChessMan() {};
	virtual bool Move(Position newPosition, Board mainBoard) = 0;

protected:
	int step = 0;
	Color color;
	Position position;
	char icon;
};