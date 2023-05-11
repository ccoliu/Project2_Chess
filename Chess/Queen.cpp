#include "Queen.h"

Queen::Queen(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'q';
	}
	else
	{
		this->icon = 'Q';
	}
};

vector<Position> Queen::Move(Position newPosition)
{
	vector<Position> accessable;
	for (int i = 0; i < 7; i++)
	{
		accessable.push_back(Position(position.y + i, position.x));
		accessable.push_back(Position(position.y - i, position.x));
		accessable.push_back(Position(position.y, position.x + i));
		accessable.push_back(Position(position.y, position.x - i));
		accessable.push_back(Position(position.y + i, position.x + i));
		accessable.push_back(Position(position.y + i, position.x - i));
		accessable.push_back(Position(position.y - i, position.x + i));
		accessable.push_back(Position(position.y - i, position.x - i));
	}
	return accessable;
}