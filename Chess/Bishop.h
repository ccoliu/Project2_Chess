//File : Bishop.h
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

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
