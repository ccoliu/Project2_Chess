#pragma once
#include "Position.h"
#include "ChessMan.h"
#include "Pawn.h"
#include "Board.h"
#include "Knight.h"
#include <iostream>
using namespace std;

class Board {
private:
	ChessMan* board[8][8];
	friend class ChessMan;
	int starting_color;
public:
	Board()
	{
		starting_color = black;
		for (int i = 0; i < 8; i++)
		{
			board[1][i] = new Pawn(white, Position(1, i));
			board[6][i] = new Pawn(black, Position(6, i));
		}
	}
	~Board()
	{
		delete[] board;
	}
	ChessMan* getChess(Position position)
	{
		return board[position.x][position.y];
	}
	void MoveChess(Position from, Position to)
	{
		ChessMan* chess = board[from.x][from.y];
		if (chess == nullptr || chess->color != starting_color)
		{
			cout << "Invalid move!" << endl;
			return;
		}
		if (chess->Move(to, *this) == true)
		{
			board[from.x][from.y] = nullptr;
			if (board[to.x][to.y] == nullptr)
			{
				chess->position = to;
				chess->step++;
				board[to.x][to.y] = chess;
			}
			starting_color = ~starting_color;
			return;
		}
		else
		{
			cout << "Invalid move!" << endl;
			return;
		}
	}
	void EatChess(Position pos)
	{
		ChessMan* chess = board[pos.x][pos.y];
		board[pos.x][pos.y] = nullptr;
		delete chess;
	}
	void Promotion(Position pos)
	{
		cout << "Enter the type of chess you want to promote to: " << endl;
		cout << "1. Queen" << endl;
		cout << "2. Rook" << endl;
		cout << "3. Bishop" << endl;
		cout << "4. Knight" << endl;
		int choice;
		retry:
		cin >> choice;
		switch (choice)
		{
			case 1:
				ChessMan * chess = getChess(pos);
				int color = chess->color;
				delete chess;
				board[pos.x][pos.y] = new Queen(color, pos);
				break;
			case 2:
				ChessMan* chess = getChess(pos);
				int color = chess->color;
				delete chess;
				board[pos.x][pos.y] = new Rook(color, pos);
				break;
			case 3:
				ChessMan* chess = getChess(pos);
				int color = chess->color;
				delete chess;
				board[pos.x][pos.y] = new Bishop(color, pos);
				break;
			case 4:
				ChessMan* chess = getChess(pos);
				int color = chess->color;
				delete chess;
				board[pos.x][pos.y] = new Knight(color, pos);
				break;
			default:
				cout << "Invalid choice!" << endl;
				goto retry;
				break;
		}
	}
};