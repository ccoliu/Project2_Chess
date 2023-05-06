#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class King : public ChessMan
{
public:
	King(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'K';
		}
		else
		{
			this->icon = 'k';
		}
	};
	vector<Position> Move(Position newPosition) override
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
};
