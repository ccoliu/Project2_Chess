#include "ViewManager.h"
#include "GameManager.h"
//constructure the ViewManager
ViewManager::ViewManager(GameManager* game)
{
	gm = game;
}
//call DrawBoard to Draw
void ViewManager::printBoard()
{
	gm->bd.DrawBoard();
}