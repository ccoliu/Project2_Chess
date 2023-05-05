#pragma once
#include "ChessMan.h"
#include <iostream>
using namespace std;

class Board {
private:
	friend class ChessMan;
	ChessMan::Color starting_color = ChessMan::Color::white;
public:
	ChessMan* board[8][8] = { nullptr };
	Board()
	{
	}
	void DrawBoard()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				ChessMan* chess = getChess(Position(i, j));
				if (chess != nullptr)
				{
					cout << chess->getIcon();
				}
				else cout << " ";
			}
			cout << endl;
		}
	}
	void initMove()
	{
		cout << "It's " << (starting_color == ChessMan::Color::white ? " white's " : " black's ") << "turn!" << endl;
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		Position from(y1, x1), to(y2, x2);
		MoveChess(from, to);
		return;
	}
	ChessMan* getChess(Position position)
	{
		return board[position.y][position.x];
	}
	void MoveChess(Position from, Position to)
	{
		if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7 || to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7)
		{
			cout << "Invalid move! a" << endl;
			return;
		}
		ChessMan* chess = board[from.y][from.x];
		if (chess == nullptr || chess->getColor() != starting_color)
		{
			if (chess == nullptr) cout << "nullptr ";
			cout << "Invalid move! b" << endl;
			return;
		}
		if (chess->Move(to, *this) == true)
		{
			board[from.y][from.x] = nullptr;
			if (board[to.y][to.x] == nullptr)
			{
				chess->position = to;
				chess->step++;
				board[to.y][to.x] = chess;
			}
			starting_color = (starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white);
			return;
		}
		else
		{
			cout << "Invalid move! c" << endl;
			return;
		}
	}
	ChessMan* EatChess(Position pos)
	{
		ChessMan* chess = getChess(pos);
		board[pos.y][pos.x] = nullptr;
		delete chess;
		return nullptr;
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
		ChessMan* chess = getChess(pos);
		ChessMan::Color color = chess->getColor();
		switch (choice)
		{
		case 1:
			//board[pos.y][pos.x] = new Queen(color, pos);
			break;
		case 2:
			//board[pos.y][pos.x] = new Rook(color, pos);
			break;
		case 3:
			//board[pos.y][pos.x] = new Bishop(color, pos);
			break;
		case 4:
			//mainBoard.board[pos.y][pos.x] = new Knight(color, pos);
			break;
		default:
			cout << "Invalid choice!" << endl;
			goto retry;
			break;
		}
		return;
	}
};