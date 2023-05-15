//File : ViewManager.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/15
//Description:Chess

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