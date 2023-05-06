#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Rook : public ChessMan
{
public:
	//initialize the rook
	Rook(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'R';
		}
		else
		{
			this->icon = 'r';
		}
	};
	vector<Position> Move(Position newPosition) override
	{
		vector<Position> accessable;
		for (int i = 1; i < 8; i++)
		{
			accessable.push_back(Position(position.y + i, position.x));
			accessable.push_back(Position(position.y - i, position.x));
			accessable.push_back(Position(position.y, position.x + i));
			accessable.push_back(Position(position.y, position.x - i));
		}
		return accessable;
	}
};
