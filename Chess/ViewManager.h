#pragma once

class GameManager;

class ViewManager
{
private:
	GameManager* gm;
public:
	ViewManager(GameManager* game);
	void printBoard();
};