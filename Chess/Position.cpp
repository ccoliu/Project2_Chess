#include "Position.h"

Position::Position()
{
	this->x = -1;
	this->y = -1;
}

Position::Position(int y, int x)
{
	this->x = x;
	this->y = y;
}

bool Position::operator==(Position position)
{
	if (this->x == position.x && this->y == position.y)
		return true;
	return false;
}