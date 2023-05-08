#pragma once
#include "ChessMan.h"
#include "Knight.h"
#include "Pawn.h"
#include <iostream>
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
using namespace std;

class Board {
private:
	friend class ChessMan;
	ChessMan::Color starting_color = ChessMan::Color::white;
	bool win = false;
	string winner = "";
public:
	ChessMan* board[8][8] = { nullptr };
	Board()
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
	int isCheckmated(Position pos)
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
							for (int k = chess->position.x, p = chess->position.y; k != pos.x && p != pos.y; ((chess->position.x <= pos.x) ? ((chess->position.x == pos.x) ? k : k++) : k--), ((chess->position.y <= pos.y) ? ((chess->position.y == pos.y) ? p : p++) : p--))
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
	void DrawBoard()
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
	void initMove()
	{
		cout << "It's" << (starting_color == ChessMan::Color::white ? " white's " : " black's ") << "turn!" << endl;
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		Position from(y1, x1), to(y2, x2);
		if (MoveChess(from, to) == true)
		{
			ChessMan* chess = board[from.y][from.x];
			board[to.y][to.x] = chess;
			chess->position = to;
			chess->step++;
			board[from.y][from.x] = nullptr;
			if (to.y == 0 || to.y == 7 && typeid(*chess) == typeid(Pawn)) Promotion(to);
			starting_color = starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white;
			if (win)
			{
				DrawBoard();
				cout << winner << endl;
				exit(0);
			}
		}
		return;
	}
	ChessMan* getChess(Position position)
	{
		return board[position.y][position.x];
	}
	bool MoveChess(Position from, Position to)
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
					else if (getChess(Position(from.y, from.x - 1)) != nullptr && typeid(*getChess(Position(from.y, from.x - 1))) == typeid(Pawn) && getChess(Position(from.y, from.x - 1))->getColor() != chess->getColor() && getChess(Position(from.y, from.x - 1))->getStep() == 1)
					{
						EatChess(Position(from.y, from.x - 1));
						return true;
					}
					else if (getChess(Position(from.y, from.x + 1)) != nullptr && typeid(*getChess(Position(from.y, from.x + 1))) == typeid(Pawn) && getChess(Position(from.y, from.x + 1))->getColor() != chess->getColor() && getChess(Position(from.y, from.x + 1))->getStep() == 1)
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
				else
				{
					return true;
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
				if (to.x == from.x)
				{
					if (to.y > from.y)
					{
						for (int i = from.y + 1; i < to.y; i++)
						{
							if (getChess(Position(i, to.x)) != nullptr)
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
					else
					{
						for (int i = from.y - 1; i > to.y; i--)
						{
							if (getChess(Position(i, to.x)) != nullptr)
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
				else
				{
					if (to.x > from.x)
					{
						for (int i = from.x + 1; i < to.x; i++)
						{
							if (getChess(Position(to.y, i)) != nullptr)
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
					else
					{
						for (int i = from.x - 1; i > to.x; i--)
						{
							if (getChess(Position(to.y, i)) != nullptr)
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
				if (to.x > from.x && to.y > from.y)
				{
					for (int i = from.x + 1, j = from.y + 1; i < to.x && j < to.y; i++, j++)
					{
						if (getChess(Position(j, i)) != nullptr)
						{
							cout << "Invalid move: Move not available!" << endl;
							return true;
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
				else if (to.x > from.x && to.y < from.y)
				{
					for (int i = from.x + 1, j = from.y - 1; i < to.x && j > to.y; i++, j--)
					{
						if (getChess(Position(j, i)) != nullptr)
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
				else if (to.x < from.x && to.y > from.y)
				{
					for (int i = from.x - 1, j = from.y + 1; i > to.x && j < to.y; i--, j++)
					{
						if (getChess(Position(j, i)) != nullptr)
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
				else
				{
					for (int i = from.x - 1, j = from.y - 1; i > to.x && j > to.y; i--, j--)
					{
						if (getChess(Position(j, i)) != nullptr)
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
		}
		else if (typeid(*chess) == typeid(Queen)) //bishop + rook
		{
			if (find(moves.begin(), moves.end(), to) == moves.end())
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
			else
			{
				if (to.x - from.x != 0 && to.y - from.y != 0) //bishop
				{
					if (to.x > from.x && to.y > from.y)
					{
						for (int i = from.x + 1, j = from.y + 1; i < to.x && j < to.y; i++, j++)
						{
							if (getChess(Position(j, i)) != nullptr)
							{
								cout << "Invalid move: Move not available!" << endl;
								return true;
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
					else if (to.x > from.x && to.y < from.y)
					{
						for (int i = from.x + 1, j = from.y - 1; i < to.x && j > to.y; i++, j--)
						{
							if (getChess(Position(j, i)) != nullptr)
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
					else if (to.x < from.x && to.y > from.y)
					{
						for (int i = from.x - 1, j = from.y + 1; i > to.x && j < to.y; i--, j++)
						{
							if (getChess(Position(j, i)) != nullptr)
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
					else
					{
						for (int i = from.x - 1, j = from.y - 1; i > to.x && j > to.y; i--, j--)
						{
							if (getChess(Position(j, i)) != nullptr)
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
				else //rook
				{
					if (to.x == from.x)
					{
						if (to.y > from.y)
						{
							for (int i = from.y + 1; i < to.y; i++)
							{
								if (getChess(Position(i, to.x)) != nullptr)
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
						else
						{
							for (int i = from.y - 1; i > to.y; i--)
							{
								if (getChess(Position(i, to.x)) != nullptr)
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
					else
					{
						if (to.x > from.x)
						{
							for (int i = from.x + 1; i < to.x; i++)
							{
								if (getChess(Position(to.y, i)) != nullptr)
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
						else
						{
							for (int i = from.x - 1; i > to.x; i--)
							{
								if (getChess(Position(to.y, i)) != nullptr)
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
				}
			}
		}
		else if (typeid(*chess) == typeid(King))
		{
			if (find(moves.begin(), moves.end(), to) == moves.end())
			{
				cout << "Invalid move: Move not available!" << endl;
				return false;
			}
			else
			{
				int Checkmate = isCheckmated(to);
				if (getChess(to) != nullptr && getChess(to)->getColor() != chess->color && Checkmate == 0)
				{
					EatChess(to);
					return true;
				}
				else if (getChess(to) == nullptr && Checkmate == 0)
				{
					return true;
				}
				else if (to.y == from.y && abs(to.x - from.x) == 2) //Castling
				{
					if (getChess(to)->getStep() != 0)
					{
						cout << "Invalid move: Move not available!" << endl;
						return false;
					}
					bool hasRook = false;
					ChessMan* rook = nullptr;
					if (to.x < from.x)
					{
						for (int i = from.x - 1; i > 0; i--)
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
							if (rook->getStep() == 0 && Checkmate == 0)
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
								if (Checkmate > 0)
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
							if (rook->getStep() == 0 && Checkmate == 0)
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
								if (Checkmate > 0)
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
	ChessMan* EatChess(Position pos)
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
	void Promotion(Position pos)
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
};