#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Knight : public ChessMan
{
public:
	Knight(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'N';
		}
		else
		{
			this->icon = 'n';
		}
	};
	vector<Position> Move(Position newPosition) override
	{
		vector<Position> accessable = { {position.y - 1, position.x - 2}, {position.y + 1, position.x - 2},
						   {position.y - 2, position.x - 1}, {position.y + 2, position.x - 1},
						   {position.y - 2, position.x + 1}, {position.y + 2, position.x + 1},
						   {position.y - 1, position.x + 2}, {position.y + 1, position.x + 2} };
		return accessable;
	}
};
