//File : Board.cpp
//Name : ¼B¥[¦¨ ¤ý¬Rµ¾ §fª@®p ³¯©|«h
//First Update:2023/5/3
//Last Update:2023/5/12
//Description:Chess
#include "Board.h"

Board::Board()
{
	//initialize pawn position
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(ChessMan::Color::black, Position(1, i));
		board[6][i] = new Pawn(ChessMan::Color::white, Position(6, i));
		board[1][i] = new Pawn(ChessMan::Color::black, Position(1, i));
		board[6][i] = new Pawn(ChessMan::Color::white, Position(6, i));
	}
	//initialize Knight position
	board[0][1] = new Knight(ChessMan::Color::black, Position(0, 1));
	board[0][6] = new Knight(ChessMan::Color::black, Position(0, 6));
	board[7][1] = new Knight(ChessMan::Color::white, Position(7, 1));
	board[7][6] = new Knight(ChessMan::Color::white, Position(7, 6));
	//initialize Rook position
	board[0][0] = new Rook(ChessMan::Color::black, Position(0, 0));
	board[0][7] = new Rook(ChessMan::Color::black, Position(0, 7));
	board[7][0] = new Rook(ChessMan::Color::white, Position(7, 0));
	board[7][7] = new Rook(ChessMan::Color::white, Position(7, 7));
	//initialize Bishop position
	board[0][2] = new Bishop(ChessMan::Color::black, Position(0, 2));
	board[0][5] = new Bishop(ChessMan::Color::black, Position(0, 5));
	board[7][2] = new Bishop(ChessMan::Color::white, Position(7, 2));
	board[7][5] = new Bishop(ChessMan::Color::white, Position(7, 5));
	//initialize Queen position
	board[0][3] = new Queen(ChessMan::Color::black, Position(0, 3));
	board[7][3] = new Queen(ChessMan::Color::white, Position(7, 3));
	//initialize King position
	board[0][4] = new King(ChessMan::Color::black, Position(0, 4));
	board[7][4] = new King(ChessMan::Color::white, Position(7, 4));
}
//check whether checkmate
int Board::isCheckmated(ChessMan* board[8][8], Position pos)
{
	int count = 0;
	//check every position whether have chess can eat king chess
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			ChessMan* chess = getChess(Position(i, j));
			if (chess == nullptr) continue;		//no chess then continue 
			if (chess->position == pos || chess->getColor() == starting_color) continue;	//if same color then skip
			vector<Position> moves = chess->Move(pos);
			{
				if (find(moves.begin(), moves.end(), pos) != moves.end())
				{
					//check Pawn if same Y position the skip because Pawn cannot eat ahead
					if (typeid(*chess) == typeid(Pawn))
					{
						if (chess->position.y == pos.y) continue;
					}
					//check Pawn Knight King
					if (typeid(*chess) == typeid(Pawn) || typeid(*chess) == typeid(Knight) || typeid(*chess) == typeid(King)) count++;
					else
					{
						bool isBlocked = false;
						int k = 0;
						int p = 0;
						if (j <= pos.x)
						{
							if (j == pos.x) k = j;
							else k = j + 1;
						}
						else k = j - 1;
						if (i <= pos.y)
						{
							if (i == pos.y) p = i;
							else p = i + 1;
						}
						else p = i - 1;
						for (k, p; k != pos.x || p != pos.y; ((chess->position.x <= pos.x) ? ((chess->position.x == pos.x) ? k : k++) : k--), ((chess->position.y <= pos.y) ? ((chess->position.y == pos.y) ? p : p++) : p--))
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
//when last step be push then go to previous step
void Board::gotoPreviousBoard()
{
	int sz = log.size() - 1;
	Position currentPos = log[sz].second;
	Position lastPos = log[sz].first;
	ChessMan* chess = getChess(currentPos);
	board[lastPos.y][lastPos.x] = board[currentPos.y][currentPos.x];
	board[currentPos.y][currentPos.x] = nullptr;
	chess->position = lastPos;
	chess->step--;
	if (typeid(*seq[sz-1]) != typeid(*chess) && typeid(*seq[sz-1]) == typeid(Pawn))
	{
		ChessMan::Color color = chess->getColor();
		int st = chess->getStep();
		delete chess;
		board[lastPos.y][lastPos.x] = nullptr;
		board[lastPos.y][lastPos.x] = new Pawn(color, lastPos);
		board[lastPos.y][lastPos.x]->step = st;
	}
	else if (typeid(*chess) == typeid(King) && abs(lastPos.x - currentPos.x) == 2)
	{
		if (chess->getColor() == ChessMan::Color::black)
		{
			if (lastPos.x > currentPos.x) // go left
			{
				board[0][0] = board[chess->position.y][chess->position.x - 1];
				board[chess->position.y][chess->position.x - 1] = nullptr;
				board[0][0]->position = Position(0, 0);
				board[0][0]->step = 0;
			}
			else // lastPos.x < currentPos.x
			{
				board[0][7] = board[chess->position.y][chess->position.x + 1];
				board[chess->position.y][chess->position.x + 1] = nullptr;
				board[0][7]->position = Position(0, 7);
				board[0][7]->step = 0;
			}
		}
		else
		{
			if (lastPos.x > currentPos.x) // go left
			{
				board[7][0] = board[chess->position.y][chess->position.x - 1];
				board[chess->position.y][chess->position.x - 1] = nullptr;
				board[7][0]->position = Position(7, 0);
				board[7][0]->step = 0;
			}
			else // lastPos.x < currentPos.x
			{
				board[7][7] = board[chess->position.y][chess->position.x + 1];
				board[chess->position.y][chess->position.x + 1] = nullptr;
				board[7][7]->position = Position(7, 7);
				board[7][7]->step = 0;
			}
		}
	}
	log.pop_back();
	int sz2 = eatLog.size() - 1;
	ChessMan* eatenChess = eatLog[sz].first;
	if (eatenChess != nullptr)
	{
		Position lastEatPos = eatLog[sz].second;
		board[lastEatPos.y][lastEatPos.x] = eatenChess;
	}
	eatLog.pop_back();
	seq.pop_back();
}
//find king position
Position Board::getKingPos()
{
	Position king_pos;
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			ChessMan* chess = getChess(Position(i, j));
			if (chess != nullptr && typeid(*chess) == typeid(King) && chess->getColor() == starting_color)
			{
				king_pos = chess->position;
			}
		}
	}
	return king_pos;
}
//if Tie return treu or return false
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
		//check Knight
		if (typeid(*chess) == typeid(Knight)) return false;
		//check Pawn
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
		//check Rook
		if (typeid(*chess) == typeid(Rook))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y)) == nullptr || (getChess(Position(pos.x - 1, pos.y)) != nullptr && getChess(Position(pos.x - 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && (getChess(Position(pos.x + 1, pos.y)) == nullptr || (getChess(Position(pos.x + 1, pos.y)) != nullptr && getChess(Position(pos.x + 1, pos.y))->getColor() != chess->getColor()))) return false;
			if (pos.y - 1 >= 0 && (getChess(Position(pos.x, pos.y - 1)) == nullptr || (getChess(Position(pos.x, pos.y - 1)) != nullptr && getChess(Position(pos.x, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.y + 1 < 8 && (getChess(Position(pos.x, pos.y + 1)) == nullptr || (getChess(Position(pos.x, pos.y + 1)) != nullptr && getChess(Position(pos.x, pos.y + 1))->getColor() != chess->getColor()))) return false;
		}
		//check Bishop
		if (typeid(*chess) == typeid(Bishop))
		{
			Position pos = chess->position;
			if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && (getChess(Position(pos.x - 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y - 1)) != nullptr && getChess(Position(pos.x - 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x - 1 >= 0 && pos.y + 1 < 8 && (getChess(Position(pos.x - 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x - 1, pos.y + 1)) != nullptr && getChess(Position(pos.x - 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y - 1 >= 0 && (getChess(Position(pos.x + 1, pos.y - 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y - 1)) != nullptr && getChess(Position(pos.x + 1, pos.y - 1))->getColor() != chess->getColor()))) return false;
			if (pos.x + 1 < 8 && pos.y + 1 < 8 && (getChess(Position(pos.x + 1, pos.y + 1)) == nullptr || (getChess(Position(pos.x + 1, pos.y + 1)) != nullptr && getChess(Position(pos.x + 1, pos.y + 1))->getColor() != chess->getColor()))) return false;
		}
		//check Queen
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
		//check King
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
	//if checkmate then no Tie and judge who win
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
//draw the board to window
void Board::DrawBoard()
{
	for (int i = 0; i < 8; i++)
	{
		cout << 8 - i << " |";
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
	cout << "  ¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð" << endl;
	cout << "   a b c d e f g h" << endl;
}

void Board::initMove()
{
	cout << "It's" << (starting_color == ChessMan::Color::white ? " white's " : " black's ") << "turn!" << endl;
	cout << "Please input position that the chess you want to move and destination (Ex: d2 d4)" << endl;
	cout << "input \"menu\" to open up menu." << endl;
	string s;
	getline(cin, s);
	//open the menu
	if (s == "menu")
	{
		cout << "Please select your choice:" << endl;
		cout << "(1) Resign" << endl;
		cout << "(2) Redo" << endl;
		cout << "(3) Exit" << endl;
		int choice;
		cin >> choice;
		cin.ignore();
		if (choice == 3) return;
		//go to last step
		if (choice == 2)
		{
			if (log.size() == 0)
			{
				cout << "No step to redo!" << endl;
				return;
			}
			gotoPreviousBoard();
			starting_color = starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white;
			return;
		}
		//give up the game
		if (choice == 1)
		{
			if (starting_color == ChessMan::Color::white)
			{
				cout << "White resigned, Black wins!" << endl;
				exit(0);
			}
			else
			{
				cout << "Black resigned, White wins!" << endl;
				exit(0);
			}
		}
	}
	if (s.length() < 5)
	{
		cout << "Error: Input Invalid" << endl;
		return;
	}
	kingPos = getKingPos();
	char x1, x2;
	int y1, y2;
	x1 = s[0];
	y1 = s[1] - '0';
	x2 = s[3];
	y2 = s[4] - '0';
	Position from(8 - y1, (x1 - 'a')), to(8 - y2, (x2 - 'a'));
	//if can move thenmove
	if (MoveChess(from, to) == true)
	{
		ChessMan* chess = board[from.y][from.x];
		board[to.y][to.x] = chess;
		chess->position = to;
		chess->step++;
		board[from.y][from.x] = nullptr;
		if ((to.y == 0 || to.y == 7) && typeid(*chess) == typeid(Pawn)) Promotion(to);	//Pawn promotion
		kingPos = getKingPos();
		log.push_back(make_pair(from, to));
		if (hasEat == false)
		{
			eatLog.push_back(make_pair(nullptr, Position(-1, -1)));
		}
		hasEat = false;
		seq.push_back(getChess(to));
		//if checkmate then print the alert and return to origin position
		if (isCheckmated(board, kingPos) != 0)
		{
			cout << "Invalid move: Checkmate alert!" << endl;
			gotoPreviousBoard();
			return;
		}
		starting_color = starting_color == ChessMan::Color::white ? ChessMan::Color::black : ChessMan::Color::white;
		//when cannot move and no win then Tie
		if (win == false && checkTie())
		{
			DrawBoard();
			cout << "Tie!" << endl;
			exit(0);
		}
		//print who win
		if (win)
		{
			DrawBoard();
			cout << winner << endl;
			exit(0);
		}
		kingPos = getKingPos();
		//if checkmate then alert the player
		if (isCheckmated(board, kingPos) > 0)
		{
			cout << "Warning: Checkmate alert." << endl;
		}
	}
	return;
}
//return the position's chess
ChessMan* Board::getChess(Position position)
{
	return board[position.y][position.x];
}
//check the next position whether can move
bool Board::MoveChess(Position from, Position to)
{
	//out of range return false
	if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7 || to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7)
	{
		cout << "Invalid move: out of range!" << endl;
		return false;
	}
	//same position return false
	if (from == to)
	{
		cout << "Invalid move: same position!" << endl;
		return false;
	}
	ChessMan* chess = board[from.y][from.x];
	//if the oringin position is null or wrong color to chose
	if (chess == nullptr || chess->getColor() != starting_color)
	{
		if (chess == nullptr) cout << "nullptr ";
		cout << "Invalid move: Chess unavailable!" << endl;
		return false;
	}
	vector<Position> moves = chess->Move(to);
	//check Pawn
	if (typeid(*chess) == typeid(Pawn))
	{
		//out oh Pawn move range
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			//call eat chess when new position is different color chess and the new position is not ahead
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
			else if (getChess(to) != nullptr && getChess(to)->getColor() != chess->getColor())
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
	//check Knight
	else if (typeid(*chess) == typeid(Knight))
	{
		//out oh Knight move range
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
	//check Rook
	else if (typeid(*chess) == typeid(Rook))
	{
		//out oh Rook move range
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x || p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
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
	//check Bishop
	else if (typeid(*chess) == typeid(Bishop))
	{
		//out oh Bishop move range
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x || p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
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
	//check Queen
	else if (typeid(*chess) == typeid(Queen))
	{
		//out oh Queen move range
		if (find(moves.begin(), moves.end(), to) == moves.end())
		{
			cout << "Invalid move: Move not available!" << endl;
			return false;
		}
		else
		{
			int k = ((from.x <= to.x) ? ((from.x == to.x ? from.x : from.x + 1)) : from.x - 1);
			int p = ((from.y <= to.y) ? ((from.y == to.y ? from.y : from.y + 1)) : from.y - 1);
			for (k, p; k != to.x || p != to.y; ((from.x <= to.x) ? ((from.x == to.x) ? k : k++) : k--), ((from.y <= to.y) ? ((from.y == to.y) ? p : p++) : p--))
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
	//check King
	else if (typeid(*chess) == typeid(King))
	{
		//out oh King move range
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
							//if checkmate print alert
							if (isCheckmated(board,to) > 0)
							{
								cout << "Invalid move: Checkmate alert!" << endl;
							}
							else
							{
								//rook has move so cannnot castling
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
			//if no checkmate and different chess then eatchess
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
//eat chess function
void Board::EatChess(Position pos)
{
	ChessMan* chess = getChess(pos);
	eatLog.push_back(make_pair(chess, pos));
	hasEat = true;
	//if king beem eat then judge win or lose
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
}
//pawn promotion
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
	cin.ignore();
	ChessMan* chess = getChess(pos);
	ChessMan::Color color = chess->getColor();
	int st = chess->getStep();
	delete chess;
	board[pos.y][pos.x] = nullptr;
	switch (choice)
	{
	case 1:
		board[pos.y][pos.x] = new Queen(color, pos);
		board[pos.y][pos.x]->step = st;
		break;
	case 2:
		board[pos.y][pos.x] = new Rook(color, pos);
		board[pos.y][pos.x]->step = st;
		break;
	case 3:
		board[pos.y][pos.x] = new Bishop(color, pos);
		board[pos.y][pos.x]->step = st;
		break;
	case 4:
		board[pos.y][pos.x] = new Knight(color, pos);
		board[pos.y][pos.x]->step = st;
		break;
	default:
		cout << "Invalid choice!" << endl;
		goto retry;
		break;
	}
	return;
}