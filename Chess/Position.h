//File : Position.h
//Name : �B�[�� ���R�� �f�@�p ���|�A
//First Update:2023/5/3
//Last Update:2023/5/15
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