#pragma once
#include <iostream>
#include <sstream>
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
	ChessMan::Color starting_color = ChessMan::Color::white;
	bool win = false;
	bool hasEat = false;
	string winner = "";
	Position kingPos;
public:
	vector<pair<Position,Position>> log;
	vector<pair<ChessMan*, Position>> eatLog;
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
};