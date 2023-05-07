#pragma once
#include "Board.h"

class GameManager
{
private:
	Board bd;
public:
	GameManager()
	{
		bd = Board();
	}
	void StartGame()
	{
		while (true)
		{
			bd.DrawBoard();
			bd.initMove();
		}
	}
};