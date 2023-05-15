//File : Position.cpp
//Name : ¼B¥[¦¨ ¤ı¬Rµ¾ §fª@®p ³¯©|¿A
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

#include "Position.h"
//constructure
Position::Position()
{
	this->x = -1;
	this->y = -1;
}
//constructure then set x and y
Position::Position(int y, int x)
{
	this->x = x;
	this->y = y;
}
//:operator== and return true or false
bool Position::operator==(Position position)
{
	if (this->x == position.x && this->y == position.y)
		return true;
	return false;
}