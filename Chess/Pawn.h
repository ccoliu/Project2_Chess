//File : Pawn.h
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#pragma once
#include "ChessMan.h"
#include "Board.h"

class Pawn : public ChessMan
{
	public:
		Pawn(Color col, Position position);
		vector<Position> Move(Position newPosition) override;
};