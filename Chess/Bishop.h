#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Bishop : public ChessMan
{
public:
	Bishop(Color col, Position position);
	vector<Position> Move(Position newPosition) override;
};
