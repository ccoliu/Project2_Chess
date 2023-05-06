#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Queen : public ChessMan
{
public:
	Queen(Color col, Position position) : ChessMan(col, position)
	{
		if (col == Color::white)
		{
			this->icon = 'Q';
		}
		else
		{
			this->icon = 'q';
		}
	};
	vector<Position> Move(Position newPosition) override
	{
		vector<Position> accessable;
		for (int i = 0; i < 7; i++)
		{
			accessable.push_back(Position(position.y + i, position.x));
			accessable.push_back(Position(position.y - i, position.x));
			accessable.push_back(Position(position.y, position.x + i));
			accessable.push_back(Position(position.y, position.x - i));
			accessable.push_back(Position(position.y + i, position.x+i));
			accessable.push_back(Position(position.y + i, position.x-i));
			accessable.push_back(Position(position.y-i, position.x + i));
			accessable.push_back(Position(position.y-i, position.x - i));
		}
		return accessable;
	}
};
