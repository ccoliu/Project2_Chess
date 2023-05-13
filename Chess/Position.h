//File : Position.h
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess

class Position
{
public:
	int x;
	int y;
	Position();
	Position(int y, int x);
	bool operator==(Position position);
};