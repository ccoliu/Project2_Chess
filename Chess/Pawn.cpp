#include "Pawn.h"

Pawn::Pawn(Color col, Position position) : ChessMan(col, position)
{
	if (col == Color::white)
	{
		this->icon = 'p';
	}
	else
	{
		this->icon = 'P';
	}
};

vector<Position> Pawn::Move(Position newPosition)
{
	if (this->color == Color::black)
	{
		if (this->step == 0)
		{
			vector<Position> possibleMove = { Position(position.y + 1, position.x), Position(position.y + 2, position.x),
											  Position(position.y + 1, position.x - 1), Position(position.y + 1, position.x + 1)};
			return possibleMove;
		}
		else
		{
			vector<Position> possibleMove = { Position(position.y + 1, position.x), Position(position.y + 1, position.x - 1),
														  Position(position.y + 1, position.x + 1) };
			return possibleMove;
		}
	}
	else
	{
		if (this->step == 0)
		{
			vector<Position> possibleMove = { Position(position.y - 1, position.x), Position(position.y - 2, position.x),
														Position(position.y - 1, position.x - 1), Position(position.y - 1, position.x + 1) };
			return possibleMove;
		}
		else
		{
			vector<Position> possibleMove = { Position(position.y - 1, position.x), Position(position.y - 1, position.x - 1),
														  Position(position.y - 1, position.x + 1) };
			return possibleMove;
		}
	}
}