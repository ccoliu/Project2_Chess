#include "ViewManager.h"
#include "GameManager.h"

ViewManager::ViewManager(GameManager* game)
{
	gm = game;
}

void ViewManager::printBoard()
{
	gm->bd.DrawBoard();
}