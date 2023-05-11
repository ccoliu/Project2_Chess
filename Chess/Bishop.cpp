#include "Bishop.h"

Bishop::Bishop(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'b';
	}
	else
	{
		this->icon = 'B';
	}
};
vector<Position> Bishop::Move(Position newPosition)
{
	vector<Position> accessable;
	for (int i = 0; i < 7; i++)
	{
		accessable.push_back(Position(position.y + i, position.x + i));
		accessable.push_back(Position(position.y + i, position.x - i));
		accessable.push_back(Position(position.y - i, position.x + i));
		accessable.push_back(Position(position.y - i, position.x - i));
	}
	return accessable;
}