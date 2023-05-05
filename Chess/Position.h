#pragma once

struct Position
{
	int x;
	int y;
	Position()
	{
		this->x = -1;
		this->y = -1;
	}
	Position(int y, int x)
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