#include "GameManager.h"

GameManager::GameManager()
{
	bd = Board();
}
void GameManager::StartGame()
{
	while (true)
	{
		bd.DrawBoard();
		bd.initMove();
	}
}