#include <iostream>
#include "Board.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
using namespace std;

int main()
{
	Board bd = Board();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bd.board[i][j] = nullptr;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		bd.board[1][i] = new Pawn(ChessMan::Color::black, Position(1, i));
		bd.board[6][i] = new Pawn(ChessMan::Color::white, Position(6, i));
	}
	bd.board[0][1] = new Knight(ChessMan::Color::black, Position(0, 1));
	bd.board[0][6] = new Knight(ChessMan::Color::black, Position(0, 6));
	bd.board[7][1] = new Knight(ChessMan::Color::white, Position(7, 1));
	bd.board[7][6] = new Knight(ChessMan::Color::white, Position(7, 6));

	bd.board[0][0] = new Rook(ChessMan::Color::black, Position(0, 0));
	bd.board[0][7] = new Rook(ChessMan::Color::black, Position(0, 7));
	bd.board[7][0] = new Rook(ChessMan::Color::white, Position(7, 0));
	bd.board[7][7] = new Rook(ChessMan::Color::white, Position(7, 7));
	while (true)
	{
		bd.DrawBoard();
		bd.initMove();
	}
}