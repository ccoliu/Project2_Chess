//File : GameManager.h
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

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