//File : GameManager.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/15
//Description:Chess

#include "GameManager.h"

//constructure
GameManager::GameManager()
{
	bd = Board();
}
//prepare the information to start game
void GameManager::StartGame()
{
	cout << "You can choose who will play first: " << endl;
	cout << "1. White" << endl;
	cout << "2. Black" << endl;
	int choice;
	cin >> choice;
	//chose color
	if (choice == 1)
	{
		bd.starting_color = ChessMan::Color::white;
	}
	else
	{
		bd.starting_color = ChessMan::Color::black;
	}
	cin.ignore();
	// play game to gameover
	while (true)
	{
		view.printBoard();
		player.playerMove(bd.starting_color);
	}
}
//print the Board
void GameManager::printBoard()
{
	view.printBoard();
}