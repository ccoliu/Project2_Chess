#pragma once
#include "ChessMan.h"
class GameManager;

class Player
{
private:
	GameManager* gm;
public:
	ChessMan::Color player_color;
	Player(ChessMan::Color color, GameManager* game);
	void playerMove(ChessMan::Color color);
};