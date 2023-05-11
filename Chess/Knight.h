#pragma once
#include "ChessMan.h"

#include <vector>
using namespace std;


class Knight : public ChessMan
{
public:
	Knight(Color col, Position position);
	vector<Position> Move(Position newPosition) override;
};
