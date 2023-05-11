#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Queen : public ChessMan
{
public:
	Queen(Color col, Position position);
	vector<Position> Move(Position newPosition) override;
};
