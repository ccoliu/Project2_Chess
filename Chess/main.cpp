#include <iostream>
#include "Board.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
using namespace std;

int main()
{
	Board bd = Board();
	
	while (true)
	{
		bd.DrawBoard();
		bd.initMove();
	}
}