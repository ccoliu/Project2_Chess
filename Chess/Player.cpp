//File : Player.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

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

