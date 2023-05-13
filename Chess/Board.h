#pragma once
//File : Board.h
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include <iostream>
#include <string>
#include <thread>
#include "ChessMan.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
using namespace std;

class Board {
private:
	friend class ChessMan;
	bool win = false;
	bool hasEat = false;
	string winner = "";
	Position kingPos;
public:
	ChessMan::Color starting_color;
	vector<pair<Position,Position>> log;
	vector<pair<ChessMan*, Position>> eatLog;
	vector<pair<string,string>> seq;
	ChessMan* board[8][8] = { nullptr };
	Board();
	void gotoPreviousBoard();
	int isCheckmated(ChessMan* board[8][8], Position pos);
	bool checkTie();
	void DrawBoard();
	void initMove();
	ChessMan* getChess(Position position);
	bool MoveChess(Position from, Position to);
	void EatChess(Position pos);
	void Promotion(Position pos);
	Position getKingPos();
};