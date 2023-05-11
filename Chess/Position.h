
class Position
{
public:
	int x;
	int y;
	Position();
	Position(int y, int x);
	bool operator==(Position position);
};