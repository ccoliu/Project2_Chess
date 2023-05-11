#pragma once
#include "ChessMan.h"
#include <vector>
using namespace std;

class Rook : public ChessMan
{
public:
	//initialize the rook
	Rook(Color col, Position position);
	vector<Position> Move(Position newPosition) override;
};
