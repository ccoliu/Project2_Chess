#include "Position.h"
#include "ChessMan.h"
#include "Board.h"
#include "Knight.h"

Knight::Knight(int C, Position position) : ChessMan(C, position)
{
	this->color = C;
	this->position = position;
}