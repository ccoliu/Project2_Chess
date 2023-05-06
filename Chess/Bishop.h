#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Bishop : public ChessMan
{
public:
	Bishop(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'B';
		}
		else
		{
			this->icon = 'b';
		}
	};
	vector<Position> Move(Position newPosition) override
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
};
