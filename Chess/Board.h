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
				ChessMan* chess = getChess(Position(j, i));
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
		cin >> x1 >> y1 >> x2 >> y2;
		Position from(y1, x1), to(y2, x2);
		MoveChess(from, to);
		return;
	}
	ChessMan* getChess(Position position)
	{
		return board[position.x][position.y];
	}
	void MoveChess(Position from, Position to)
	{
		if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7 || to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7)
		{
			cout << "Invalid move! a" << endl;
			return;
		}
		ChessMan* chess = board[from.x][from.y];
		if (chess == nullptr)
		{
			if (chess == nullptr) cout << "nullptr ";
			cout << "Invalid move! b" << endl;
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
			starting_color = (starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white);
			return;
		}
		else
		{
			cout << "Invalid move! c" << endl;
			return;
		}
	}
	void EatChess(Position pos)
	{
		ChessMan* chess = board[pos.x][pos.y];
		board[pos.x][pos.y] = nullptr;
		return;
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
		ChessMan::Color color = chess->color;
		switch (choice)
		{
			case 1:
				//delete chess;
				//board[pos.x][pos.y] = new Queen(color, pos);
				break;
			case 2:
				//delete chess;
				//board[pos.x][pos.y] = new Rook(color, pos);
				break;
			case 3:
				//delete chess;
				//board[pos.x][pos.y] = new Bishop(color, pos);
				break;
			case 4:
				//delete chess;
				//board[pos.x][pos.y] = new Knight(color, pos);
				break;
			default:
				cout << "Invalid choice!" << endl;
				goto retry;
				break;
		}
		return;
	}
};