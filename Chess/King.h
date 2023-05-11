#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class King : public ChessMan
{
public:
	King(Color col, Position position);
	vector<Position> Move(Position newPosition) override;
};
