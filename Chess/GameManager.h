#pragma once
#include "ChessMan.h"
#include "Board.h"
#include "Player.h"
#include "ViewManager.h"

class GameManager
{
private:
	Player player = Player(ChessMan::Color::white, this);
	ViewManager view = ViewManager(this);
public:
	Board bd;
	GameManager();
	void StartGame();
	void printBoard();
};