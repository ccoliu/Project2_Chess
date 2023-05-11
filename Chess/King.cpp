#include "King.h"

King::King(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'k';
	}
	else
	{
		this->icon = 'K';
	}
};
vector<Position> King::Move(Position newPosition)
{
	vector<Position> accessable;
	accessable.push_back(Position(position.y + 1, position.x + 1));
	accessable.push_back(Position(position.y + 1, position.x - 1));
	accessable.push_back(Position(position.y - 1, position.x + 1));
	accessable.push_back(Position(position.y - 1, position.x - 1));
	accessable.push_back(Position(position.y + 1, position.x));
	accessable.push_back(Position(position.y - 1, position.x));
	accessable.push_back(Position(position.y, position.x + 1));
	accessable.push_back(Position(position.y, position.x - 1));
	return accessable;
}