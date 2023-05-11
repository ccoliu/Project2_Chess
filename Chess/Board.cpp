#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(ChessMan::Color::black, Position(1, i));
		board[6][i] = new Pawn(ChessMan::Color::white, Position(6, i));
	}
	board[0][1] = new Knight(ChessMan::Color::black, Position(0, 1));
	board[0][6] = new Knight(ChessMan::Color::black, Position(0, 6));
	board[7][1] = new Knight(ChessMan::Color::white, Position(7, 1));
	board[7][6] = new Knight(ChessMan::Color::white, Position(7, 6));

	board[0][0] = new Rook(ChessMan::Color::black, Position(0, 0));
	board[0][7] = new Rook(ChessMan::Color::black, Position(0, 7));
	board[7][0] = new Rook(ChessMan::Color::white, Position(7, 0));
	board[7][7] = new Rook(ChessMan::Color::white, Position(7, 7));

	board[0][2] = new Bishop(ChessMan::Color::black, Position(0, 2));
	board[0][5] = new Bishop(ChessMan::Color::black, Position(0, 5));
	board[7][2] = new Bishop(ChessMan::Color::white, Position(7, 2));
	board[7][5] = new Bishop(ChessMan::Color::white, Position(7, 5));

	board[0][3] = new Queen(ChessMan::Color::black, Position(0, 3));
	board[7][3] = new Queen(ChessMan::Color::white, Position(7, 3));

	board[0][4] = new King(ChessMan::Color::black, Position(0, 4));
	board[7][4] = new King(ChessMan::Color::white, Position(7, 4));
}

int Board::isCheckmated(ChessMan* board[8][8], Position pos)
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			ChessMan* chess = getChess(Position(i, j));
			if (chess == nullptr) continue;
			if (chess->position == pos || chess->getColor() == starting_color) continue;
			vector<Position> moves = chess->Move(pos);
			{
				if (find(moves.begin(), moves.end(), pos) != moves.end())
				{
					if (typeid(*chess) == typeid(Pawn))
					{
						if (chess->position.y == pos.y) continue;
					}
					if (typeid(*chess) == typeid(Pawn) || typeid(*chess) == typeid(Knight) || typeid(*chess) == typeid(King)) count++;
					else
					{
						bool isBlocked = false;
						int k = ((chess->position.x <= pos.x) ? ((chess->position.x == pos.x ? chess->position.x : chess->position.x + 1)) : chess->position.x - 1);
						int p = ((chess->position.y <= pos.y) ? ((chess->position.y == pos.y ? chess->position.y : chess->position.y + 1)) : chess->position.y - 1);
						for (k, p; k != pos.x && p != pos.y; ((chess->position.x <= pos.x) ? ((chess->position.x == pos.x) ? k : k++) : k--), ((chess->position.y <= pos.y) ? ((chess->position.y == pos.y) ? p : p++) : p--))
						{
							if (getChess(Position(p, k)) != nullptr)
							{
								isBlocked = true;
								break;
							}
						}
						if (isBlocked == false) count++;
					}
				}
			}
		}
	}
	return count;
}

void Board::saveCurrentBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			previousboard[i][j] = board[i][j];
		}
	}
}

void Board::gotoPreviousBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = previousboard[i][j];
		}
	}
}

bool Board::checkTie()
{
	vector<ChessMan*> chesses;
	Position king_pos;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessMan* chess = getChess(Position(i, j));
			if (chess != nullptr && chess->getColor() == starting_color)
			{
				chesses.push_back(chess);
			}
			if (chess != nullptr && typeid(*chess) == typeid(King) && chess->getColor() == starting_color)
			{
				king_pos = chess->position;
			}
		}
	}
	for (int i = 0; i < chesses.size(); i++) //check every chess if that chess can move, than it is not tie
	{
		ChessMan* chess = chesses[i];
		if (typeid(*chess) == typeid(Knight)) return false;
		if (typeid(*chess) == typeid(Pawn))
		{
			Position pos = chess->position;
			if (chess->getColor() == ChessMan::Color::white)
			{
				if (getChess(Position(pos.x + 1, pos.y)) == nullptr) return false;
				if (getChess(Position(pos.x + 1, pos.y + 1)) != nullptr && getChess(Position(pos.x + 1, pos.y + 1))->getColor() != chess->getColor()) return false;
				if (getChess(Position(pos.x + 1, pos.y - 1)) != nullptr && getChess(Position(pos.x + 1, pos.y - 1))->getColor() != chess->getColor()) return false;
				if (getChess(Position(pos.x + 1, pos.y)) != nullptr && typeid(*getChess(Position(pos.x + 1, pos.y))) == typeid(Pawn) && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor() && getChess(Position(pos.x + 1, pos.y))->getStep() == 1) return false;
				if (getChess(Position(pos.x - 1, pos.y)) != nullptr && typeid(*getChess(Position(pos.x - 1, pos.y))) == typeid(Pawn) && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor() && getChess(Position(pos.x - 1, pos.y))->getStep() == 1) return false;
			}
			else
			{
				if (getChess(Position(pos.x - 1, pos.y)) == nullptr) return false;
				if (getChess(Position(pos.x - 1, pos.y + 1)) != nullptr && getChess(Position(pos.x - 1, pos.y + 1))->getColor() != chess->getColor()) return false;
				if (getChess(Position(pos.x - 1, pos.y - 1)) != nullptr && getChess(Position(pos.x - 1, pos.y - 1))->getColor() != chess->getColor()) return false;
				if (getChess(Position(pos.x - 1, pos.y)) != nullptr && typeid(*getChess(Position(pos.x - 1, pos.y))) == typeid(Pawn) && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor() && getChess(Position(pos.x - 1, pos.y))->getStep() == 1) return false;
				if (getChess(Position(pos.x + 1, pos.y)) != nullptr && typeid(*getChess(Position(pos.x + 1, pos.y))) == typeid(Pawn) && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor() && getChess(Position(pos.x + 1, pos.y))->getStep() == 1) return false;
			}
		}
		if (typeid(*chess) == typeid(Rook))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y)) == nullptr || (getChess(Position(pos.x - 1, pos.y)) != nullptr && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && (getChess(Position(pos.x + 1, pos.y)) == nullptr || (getChess(Position(pos.x + 1, pos.y)) != nullptr && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.y - 1 >= 0 && (getChess(Position(pos.x, pos.y - 1)) == nullptr || (getChess(Position(pos.x, pos.y - 1)) != nullptr && getChess(Position(pos.x, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.y + 1 < 8 && (getChess(Position(pos.x, pos.y + 1)) == nullptr || (getChess(Position(pos.x, pos.y + 1)) != nullptr && getChess(Position(pos.x, pos.y + 1))->getColor() != chess->getColor()))) return false;
		}
		if (typeid(*chess) == typeid(Bishop))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y - 1)) != nullptr && getChess(Position(pos.x - 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x - 1 >= 0 && pos.y + 1 < 8 && (getChess(Position(pos.x - 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y + 1)) != nullptr && getChess(Position(pos.x - 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y - 1 >= 0 && (getChess(Position(pos.x + 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y - 1)) != nullptr && getChess(Position(pos.x + 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y + 1 < 8 && (getChess(Position(pos.x + 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y + 1)) != nullptr && getChess(Position(pos.x + 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
		}
		if (typeid(*chess) == typeid(Queen))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y)) == nullptr || (getChess(Position(pos.x - 1, pos.y)) != nullptr && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && (getChess(Position(pos.x + 1, pos.y)) == nullptr || (getChess(Position(pos.x + 1, pos.y)) != nullptr && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.y - 1 >= 0 && (getChess(Position(pos.x, pos.y - 1)) == nullptr || (getChess(Position(pos.x, pos.y - 1)) != nullptr && getChess(Position(pos.x, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.y + 1 < 8 && (getChess(Position(pos.x, pos.y + 1)) == nullptr || (getChess(Position(pos.x, pos.y + 1)) != nullptr && getChess(Position(pos.x, pos.y + 1))->getColor() != chess->getColor()))) return false;
			if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y - 1)) != nullptr && getChess(Position(pos.x - 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x - 1 >= 0 && pos.y + 1 < 8 && (getChess(Position(pos.x - 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y + 1)) != nullptr && getChess(Position(pos.x - 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y - 1 >= 0 && (getChess(Position(pos.x + 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y - 1)) != nullptr && getChess(Position(pos.x + 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y + 1 < 8 && (getChess(Position(pos.x + 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y + 1)) != nullptr && getChess(Position(pos.x + 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
		}
		if (typeid(*chess) == typeid(King))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y)) == nullptr || (getChess(Position(pos.x - 1, pos.y)) != nullptr && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor())) && isCheckmated(board,Position(pos.x - 1, pos.y)) == 0) return false;
			if (pos.x + 1 < 8 && (getChess(Position(pos.x + 1, pos.y)) == nullptr || (getChess(Position(pos.x + 1, pos.y)) != nullptr && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x + 1, pos.y)) == 0) return false;
			if (pos.y - 1 >= 0 && (getChess(Position(pos.x, pos.y - 1)) == nullptr || (getChess(Position(pos.x, pos.y - 1)) != nullptr && getChess(Position(pos.x, pos.y - 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x, pos.y - 1)) == 0) return false;
			if (pos.y + 1 < 8 && (getChess(Position(pos.x, pos.y + 1)) == nullptr || (getChess(Position(pos.x, pos.y + 1)) != nullptr && getChess(Position(pos.x, pos.y + 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x, pos.y + 1)) == 0) return false;
			if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y - 1)) != nullptr && getChess(Position(pos.x - 1, pos.y - 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x - 1, pos.y - 1)) == 0) return false;
			if (pos.x - 1 >= 0 && pos.y + 1 < 8 && (getChess(Position(pos.x - 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y + 1)) != nullptr && getChess(Position(pos.x - 1, pos.y + 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x - 1, pos.y + 1)) == 0) return false;
			if (pos.x + 1 < 8 && pos.y - 1 >= 0 && (getChess(Position(pos.x + 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y - 1)) != nullptr && getChess(Position(pos.x + 1, pos.y - 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x + 1, pos.y - 1)) == 0) return false;
			if (pos.x + 1 < 8 && pos.y + 1 < 8 && (getChess(Position(pos.x + 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y + 1)) != nullptr && getChess(Position(pos.x + 1, pos.y + 1))->getColor() != chess->getColor())) && isCheckmated(board, Position(pos.x + 1, pos.y + 1)) == 0) return false;
			if (chess->getColor() == ChessMan::Color::white && chess->getStep() == 0) //check if we can do castling
			{
				if (getChess(Position(7, 7)) != nullptr && typeid(*getChess(Position(7, 7))) == typeid(Rook) && getChess(Position(7, 7))->getColor() == ChessMan::Color::white && getChess(Position(7, 5)) == nullptr && getChess(Position(7, 6)) == nullptr) return false;
				if (getChess(Position(7, 0)) != nullptr && typeid(*getChess(Position(7, 0))) == typeid(Rook) && getChess(Position(7, 0))->getColor() == ChessMan::Color::white && getChess(Position(7, 1)) == nullptr && getChess(Position(7, 2)) == nullptr && getChess(Position(7, 3)) == nullptr) return false;
			}
			else if (chess->getColor() == ChessMan::Color::black && chess->getStep() == 0)
			{
				if (getChess(Position(0, 7)) != nullptr && typeid(*getChess(Position(0, 7))) == typeid(Rook) && getChess(Position(0, 7))->getColor() == ChessMan::Color::black && getChess(Position(0, 5)) == nullptr && getChess(Position(0, 6)) == nullptr) return false;
				if (getChess(Position(0, 0)) != nullptr && typeid(*getChess(Position(0, 0))) == typeid(Rook) && getChess(Position(0, 0))->getColor() == ChessMan::Color::black && getChess(Position(0, 1)) == nullptr && getChess(Position(0, 2)) == nullptr && getChess(Position(0, 3)) == nullptr) return false;
			}
		}
	}
	if (isCheckmated(board,Position(king_pos.y, king_pos.x)) != 0)
	{
		win = true;
		if (getChess(Position(king_pos.y, king_pos.x))->getColor() == ChessMan::Color::white)
		{
			winner = "Black wins!";
		}
		else
		{
			winner = "White wins!";
		}
	}
	return true;
}

void Board::DrawBoard()
{
	for (int i = 0; i < 8; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 8; j++)
		{
			ChessMan* chess = getChess(Position(i, j));
			if (chess != nullptr)
			{
				cout << chess->getIcon() << " ";
			}
			else cout << ". ";
		}
		cout << endl;
	}
	cout << "  0 1 2 3 4 5 6 7" << endl;
}

void Board::initMove()
{
	cout << "It's" << (starting_color == ChessMan::Color::white ? " white's " : " black's ") << "turn!" << endl;
	int x1, y1, x2, y2;
	cin >> y1 >> x1 >> y2 >> x2;
	Position from(y1, x1), to(y2, x2);
	if (MoveChess(from, to) == true)
	{
		saveCurrentBoard();
		ChessMan* chess = board[from.y][from.x];
		board[to.y][to.x] = chess;
		chess->position = to;
		chess->step++;
		board[from.y][from.x] = nullptr;
		if ((to.y == 0 || to.y == 7) && typeid(*chess) == typeid(Pawn)) Promotion(to);
		if (isCheckmated(board, to) != 0 && isCheckmated(previousboard, to) == 0)
		{
			gotoPreviousBoard();
		}
		else
		{
			starting_color = starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white;
		}
		if (checkTie())
		{
			DrawBoard();
			cout << "Tie!" << endl;
			exit(0);
		}
		if (win)
		{
			DrawBoard();
			cout << winner << endl;
			exit(0);
		}
	}
	return;
}

ChessMan* Board::getChess(Position position)
{
	return board[position.y][position.x];
}

bool Board::MoveChess(Position from, Position to)
{
	if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7 || to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7)
	{
		cout << "Invalid move: out of range!" << endl;
		return false;
	}
	if (from == to)
	{
		cout << "Invalid move: same position!" << endl;
		return false;
	}
	ChessMan* chess = board[from.y][from.x];
	if (chess == nullptr || chess->getColor() != starting_color)
	{
		if (chess == nullptr) cout << "nullptr ";
		cout << "Invalid move: Chess unavailable!" << endl;
		return false;
	}
	vector<Position> moves = chess->Move(to);
	if (typeid(*chess) == typeid(Pawn))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			if (to.x - from.x != 0 && to.y - from.y != 0)
			{
				if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
				{
					EatChess(to);
					return true;
				}
				else if (getChess(Position(from.y, from.x - 1)) != nullptr && typeid(*getChess(Position(from.y, from.x - 1))) == typeid(Pawn) && getChess(Position(from.y, from.x - 1))->getColor() != chess->getColor() && getChess(Position(from.y, from.x - 1))->getStep() == 1 && (from.y == 3 || from.y == 4))
				{
					EatChess(Position(from.y, from.x - 1));
					return true;
				}
				else if (getChess(Position(from.y, from.x + 1)) != nullptr && typeid(*getChess(Position(from.y, from.x + 1))) == typeid(Pawn) && getChess(Position(from.y, from.x + 1))->getColor() != chess->getColor() && getChess(Position(from.y, from.x + 1))->getStep() == 1 && (from.y == 3 || from.y == 4))
				{
					EatChess(Position(from.y, from.x + 1));
					return true;
				}
				else
				{
					cout << "Invalid move: Move not available!" << endl;
					return false;
				}
			}
			else if (getChess(to) == nullptr)
			{
				return true;
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
	}
	else if (typeid(*chess) == typeid(Knight))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
			{
				EatChess(to);
				return true;
			}
			else if (getChess(to) == nullptr)
			{
				return true;
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
	}
	else if (typeid(*chess) == typeid(Rook))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x && p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
			{
				if (getChess(Position(p, k)) != nullptr)
				{
					cout << "Invalid move: Move not available!" << endl;
					return false;
				}
			}
			if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
			{
				EatChess(to);
				return true;
			}
			else if (getChess(to) == nullptr)
			{
				return true;
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
	}
	else if (typeid(*chess) == typeid(Bishop))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x && p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
			{
				if (getChess(Position(p, k)) != nullptr)
				{
					cout << "Invalid move: Move not available!" << endl;
					return false;
				}
			}
			if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
			{
				EatChess(to);
				return true;
			}
			else if (getChess(to) == nullptr)
			{
				return true;
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
	}
	else if (typeid(*chess) == typeid(Queen))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x && p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
			{
				if (getChess(Position(p, k)) != nullptr)
				{
					cout << "Invalid move: Move not available!" << endl;
					return false;
				}
			}
			if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
			{
				EatChess(to);
				return true;
			}
			else if (getChess(to) == nullptr)
			{
				return true;
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
	}
	else if (typeid(*chess) == typeid(King))
	{
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			if (to.y == from.y && abs(to.x - from.x) == 2) //Castling
			{
				if (getChess(from)->getStep() != 0)
				{
					cout << "Invalid move: Move not available!" << endl;
					return false;
				}
				bool hasRook = false;
				ChessMan* rook = nullptr;
				if (to.x < from.x)
				{
					for (int i = from.x - 1; i >= 0; i--)
					{
						if (getChess(Position(to.y, i)) == nullptr) continue;
						if (typeid(*getChess(Position(to.y, i))) == typeid(Rook))
						{
							hasRook = true;
							rook = getChess(Position(to.y, i));
						}
						else if (getChess(Position(to.y, i)) != nullptr)
						{
							cout << "Invalid move: Move not available!" << endl;
							return false;
						}
					}
					if (!hasRook)
					{
						cout << "Invalid move: No rook for castling!" << endl;
						return false;
					}
					else
					{
						if (rook->getStep() == 0 && isCheckmated(board,to) == 0)
						{
							Position rookPos = rook->position;
							board[to.y][to.x + 1] = rook;
							rook->position = Position(to.y, to.x + 1);
							rook->step++;
							board[rookPos.y][rookPos.x] = nullptr;
							return true;
						}
						else
						{
							if (isCheckmated(board,to) > 0)
							{
								cout << "Invalid move: Checkmate alert!" << endl;
							}
							else
							{
								cout << "Invalid move: Rook has moved!" << endl;
							}
							return false;
						}
					}
				}
				else
				{
					for (int i = from.x + 1; i < 8; i++)
					{
						if (typeid(*getChess(Position(to.y, i))) == typeid(Rook))
						{
							hasRook = true;
							rook = getChess(Position(to.y, i));
						}
						if (getChess(Position(to.y, i)) != nullptr)
						{
							cout << "Invalid move: Move not available!" << endl;
							return false;
						}
					}
					if (!hasRook)
					{
						cout << "Invalid move: No rook for castling!" << endl;
						return false;
					}
					else
					{
						if (rook->getStep() == 0 && isCheckmated(board,to) == 0)
						{
							Position rookPos = rook->position;
							board[to.y][to.x - 1] = rook;
							rook->position = Position(to.y, to.x - 1);
							rook->step++;
							board[rookPos.y][rookPos.x] = nullptr;
							return true;
						}
						else
						{
							if (isCheckmated(board,to) > 0)
							{
								cout << "Invalid move: Checkmate alert!" << endl;
							}
							else
							{
								cout << "Invalid move: Rook has moved!" << endl;
							}
							return false;
						}
					}
				}
			}
			else
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
		}
		else
		{
			int Checkmate = isCheckmated(board,to);
			if (getChess(to) != nullptr && getChess(to)->getColor() != chess->color && Checkmate == 0)
			{
				EatChess(to);
				return true;
			}
			else if (getChess(to) == nullptr && Checkmate == 0)
			{
				return true;
			}
			else
			{
				if (Checkmate > 0)
				{
					cout << "Invalid move: Checkmate alert!" << endl;
				}
				else
				{
					cout << "Invalid move: Move not available!" << endl;
				}
				return false;
			}
		}
	}
}

ChessMan* Board::EatChess(Position pos)
{
	ChessMan* chess = getChess(pos);
	if (typeid(*chess) == typeid(King))
	{
		win = true;
		if (chess->getColor() == ChessMan::Color::white)
		{
			winner = "Black wins!";
		}
		else
		{
			winner = "White wins!";
		}
	}
	board[pos.y][pos.x] = nullptr;
	delete chess;
	return nullptr;
}

void Board::Promotion(Position pos)
{
	cout << "Enter the type of chess you want to promote to: " << endl;
	cout << "1. Queen" << endl;
	cout << "2. Rook" << endl;
	cout << "3. Bishop" << endl;
	cout << "4. Knight" << endl;
	int choice;
retry:
	cin >> choice;
	ChessMan* chess = getChess(pos);
	ChessMan::Color color = chess->getColor();
	delete chess;
	board[pos.y][pos.x] = nullptr;
	switch (choice)
	{
	case 1:
		board[pos.y][pos.x] = new Queen(color, pos);
		break;
	case 2:
		board[pos.y][pos.x] = new Rook(color, pos);
		break;
	case 3:
		board[pos.y][pos.x] = new Bishop(color, pos);
		break;
	case 4:
		board[pos.y][pos.x] = new Knight(color, pos);
		break;
	default:
		cout << "Invalid choice!" << endl;
		goto retry;
		break;
	}
	return;
}