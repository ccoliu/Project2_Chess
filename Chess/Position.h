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
	friend istream &operator>> (istream& in, Position& pos)
	{
		in >> pos.x >> pos.y;
		return in;
	}
};