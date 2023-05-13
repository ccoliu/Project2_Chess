#include "Player.h"
#include "GameManager.h"
//constructure
Player::Player(ChessMan::Color color, GameManager* game)
{
	player_color = color;
	gm = game;
}

void Player::playerMove(ChessMan::Color color)
{
	player_color = color;
	gm->bd.initMove();
}

