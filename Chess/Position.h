#pragma once

struct Position
{
	int x;
	int y;
	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(Position position)
	{
		if (this->x == position.x && this->y == position.y)
			return true;
		return false;
	}
};