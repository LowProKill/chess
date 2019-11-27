#include "AI.h"

AI::AI()
{

}

void AI::input(char whiteBoard[10][10], char blackBoard[10][10])
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			this->whiteBoard[x][y] = whiteBoard[x][y];
			this->blackBoard[x][y] = blackBoard[x][y];
		}
	}
}

int AI::move()
{
	int position[2];
	int location[2];
	int best = -99999;
	int numBest = 0;
	bMoves bestMoves[200];

	int moveNum = AI::initialize();
	char takenPiece;

	std::cout << moveNum << std::endl;

	

	for (int x = 0; x < moveNum; x++)
	{
		position[0] = avialableMoves[x].move / 1000;
		position[1] = (avialableMoves[x].move - position[0] * 1000) / 100;
		location[0] = (avialableMoves[x].move - position[0] * 1000 - position[1] * 100) / 10;
		location[1] = avialableMoves[x].move % 10;

		takenPiece = whiteBoard[position[0]][position[1]];
		blackBoard[position[0]][position[1]] = blackBoard[location[0]][location[1]];
		whiteBoard[position[0]][position[1]] = '0';
		blackBoard[location[0]][location[1]] = '0';

		avialableMoves[x].updateBoard(whiteBoard, blackBoard);
		avialableMoves[x].countEmUp();

		whiteBoard[position[0]][position[1]] = takenPiece;
		blackBoard[location[0]][location[1]] = blackBoard[position[0]][position[1]];
		blackBoard[position[0]][position[1]] = '0';
	}

	for (int x = 0; x < moveNum; x++)
	{
		std::cout << avialableMoves[x].score << " " << avialableMoves[x].move << std::endl;
	}



	for (int x = 0; x < moveNum; x++)
	{
		if (avialableMoves[x].score > best)
		{
			best = avialableMoves[x].score;
		}
	}

	for (int x = 0; x < moveNum; x++)
	{
		if (avialableMoves[x].score == best)
		{
			bestMoves[numBest].move = avialableMoves[x].move;
			bestMoves[numBest].score = avialableMoves[x].score;
			numBest++;
		}
	}

	numBest--;
	srand(time(NULL));

	if (numBest == 0)
	{
		return bestMoves[0].move;
	}
	int theMove = rand() % numBest;
	std::cout << bestMoves[theMove].move << " " << theMove << std::endl;
	if (bestMoves[theMove].move == -1)
	{
		theMove = rand() % moveNum;
		std::cout << avialableMoves[theMove].move << " " << theMove << std::endl;
		return avialableMoves[theMove].move;
	}
	return bestMoves[theMove].move;
}

int AI::initialize()
{
	int position[2];
	int moveNum = 0;
	for (int x = 0; x < AMOVESIZE; x++)
	{
		avialableMoves[x].updateBoard(whiteBoard, blackBoard);
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			
			if (blackBoard[x][y] != '0' && blackBoard[x][y] != 'O')
			{
				position[0] = x;
				position[1] = y;
				AI::moveReset();
				AI::AIswitch(position);
				AI::blackNoMoveInCheck(position);
				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							if (moveNum > AMOVESIZE)
							{
								return moveNum;
							}
							avialableMoves[moveNum].move = inX * 1000 + inY * 100 + x * 10 + y;
							moveNum++;
						}
					}
				}
			}
		}
	}
	return moveNum;
}

int AI::countEmUp()
{
	int white = 0;
	int black = 0;

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 'O')
			{
				switch (whiteBoard[x][y])
				{
				case 'p':
					white = white + pawnStat;
					break;

				case 'n':
					white = white + knightStat;
					break;

				case 'b':
					white = white + bishopStat;
					break;

				case 'r':
					white = white + rookStat;
					break;

				case 'q':
					white = white + queenStat;
					break;

				case 'k':
					white = white + kingStat;
					break;

				default:
					break;
				}
			}
			if (blackBoard[x][y] != '0' && blackBoard[x][y] != 'O')
			{
				switch (blackBoard[x][y])
				{
				case 'p':
					black = black + pawnStat;
					break;

				case 'n':
					black = black + knightStat;
					break;

				case 'b':
					black = black + bishopStat;
					break;

				case 'r':
					black = black + rookStat;
					break;

				case 'q':
					black = black + queenStat;
					break;

				case 'k':
					black = black + kingStat;
					break;

				default:
					break;
				}
			}
		}
	}
	return black - white;
}

void AI::blackNoMoveInCheck(int position[])
{
	int legalMoves[10][10];
	char takenPiece;
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			legalMoves[x][y] = moves[x][y];
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (legalMoves[x][y] == true)
			{
				takenPiece = whiteBoard[x][y];
				blackBoard[x][y] = blackBoard[position[0]][position[1]];
				whiteBoard[x][y] = '0';
				blackBoard[position[0]][position[1]] = '0';
				if (blackCheck() == true)
				{
					legalMoves[x][y] = false;
				}
				whiteBoard[x][y] = takenPiece;
				blackBoard[position[0]][position[1]] = blackBoard[x][y];
				blackBoard[x][y] = '0';
			}
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
}

bool AI::blackCheck()
{
	int position[2];

	int KingX = 8;
	int KingY = 8;

	bool enemy = false;

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = false;
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (blackBoard[x][y] == 'k')
			{
				KingX = x;
				KingY = y;
			}
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{

			if (whiteBoard[x][y] != '0')
			{
				position[0] = x;
				position[1] = y;
				whiteSwitch(position, 0);
			}
		}
	}

	if (moves[KingX][KingY] == true)
	{
		return true;
	}
	return false;
}

void AI::AIswitch(int position[])
{
	bool castle = false;


	int origonalX = position[0];
	int origonalY = position[1];

	bool enemy = false;
	bool check = false;

	bool castleQueenside = false;
	bool castleKingside = false;

	switch (blackBoard[origonalX][origonalY])
	{
	case 'p': //=============================================================================
		if (origonalY != 7)
		{
			if (blackBoard[origonalX - 1][origonalY + 1] == '0' && whiteBoard[origonalX - 1][origonalY + 1] == '0')
			{
				moves[origonalX - 1][origonalY + 1] = true;
			}
			/*if (blackBoard[origonalX][origonalY + 1] == '0' && whiteBoard[origonalX][origonalY + 1] == '0'
			&& blackBoard[origonalX][origonalY + 2] == '0' && whiteBoard[origonalX][origonalY + 2] == '0'
			&& origonalY == 1)
			{
			moves[origonalX][origonalY + 2] = true;
			}*/

			if (whiteBoard[origonalX - 1][origonalY] != '0')
			{
				moves[origonalX - 1][origonalY] = true;
			}
			if (whiteBoard[origonalX][origonalY + 1] != '0')
			{
				moves[origonalX][origonalY + 1] = true;
			}
		}
		break;
	case 'r': //=============================================================================
		enemy = false;
		for (int y = 1; origonalY + y < BOARDSIZE && blackBoard[origonalX][origonalY + y] == '0' && enemy == false; y++)
		{
			if (blackBoard[origonalX][origonalY + y] == '0' && whiteBoard[origonalX][origonalY + y] == '0')
			{
				moves[origonalX][origonalY + y] = true;
			}
			if (whiteBoard[origonalX][origonalY + y] != '0')
			{
				moves[origonalX][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int y = 1; origonalY - y >= 0 && blackBoard[origonalX][origonalY - y] == '0' && enemy == false; y++)
		{
			if (blackBoard[origonalX][origonalY - y] == '0' && whiteBoard[origonalX][origonalY - y] == '0')
			{
				moves[origonalX][origonalY - y] = true;
			}
			if (whiteBoard[origonalX][origonalY - y] != '0')
			{
				moves[origonalX][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX + x < BOARDSIZE && blackBoard[origonalX + x][origonalY] == '0' && enemy == false; x++)
		{
			if (blackBoard[origonalX + x][origonalY] == '0' && whiteBoard[origonalX + x][origonalY] == '0')
			{
				moves[origonalX + x][origonalY] = true;
			}
			if (whiteBoard[origonalX + x][origonalY] != '0')
			{
				moves[origonalX + x][origonalY] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX - x >= 0 && blackBoard[origonalX - x][origonalY] == '0' && enemy == false; x++)
		{
			if (blackBoard[origonalX - x][origonalY] == '0' && whiteBoard[origonalX - x][origonalY] == '0')
			{
				moves[origonalX - x][origonalY] = true;
			}
			if (whiteBoard[origonalX - x][origonalY] != '0')
			{
				moves[origonalX - x][origonalY] = true;
				enemy = true;
			}
		}

		break;
	case 'n': //=============================================================================
		if (blackBoard[origonalX + 2][origonalY + 1] == '0'
			&& origonalX + 2 < BOARDSIZE && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX + 2][origonalY + 1] = true;
		}
		if (blackBoard[origonalX + 1][origonalY + 2] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY + 2 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY + 2] = true;
		}
		if (blackBoard[origonalX - 1][origonalY + 2] == '0'
			&& origonalX - 1 >= 0 && origonalY + 2 < BOARDSIZE)
		{
			moves[origonalX - 1][origonalY + 2] = true;
		}
		if (blackBoard[origonalX - 2][origonalY + 1] == '0'
			&& origonalX - 2 >= 0 && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX - 2][origonalY + 1] = true;
		}

		if (blackBoard[origonalX + 2][origonalY - 1] == '0'
			&& origonalX + 2 < BOARDSIZE && origonalY - 1 >= 0)
		{
			moves[origonalX + 2][origonalY - 1] = true;
		}
		if (blackBoard[origonalX + 1][origonalY - 2] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY - 2 >= 0)
		{
			moves[origonalX + 1][origonalY - 2] = true;
		}
		if (blackBoard[origonalX - 1][origonalY - 2] == '0'
			&& origonalX - 1 >= 0 && origonalY - 2 >= 0)
		{
			moves[origonalX - 1][origonalY - 2] = true;
		}
		if (blackBoard[origonalX - 2][origonalY - 1] == '0'
			&& origonalX - 2 >= 0 && origonalY - 1 >= 0)
		{
			moves[origonalX - 2][origonalY - 1] = true;
		}
		break;
	case 'b': //=============================================================================
		enemy = false;
		for (int x = 1, y = 1; x + origonalX < BOARDSIZE
			&& origonalY + y < BOARDSIZE && blackBoard[origonalX + x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX + x][origonalY + y] == '0' && whiteBoard[origonalX + x][origonalY + y] == '0')
			{
				moves[origonalX + x][origonalY + y] = true;
			}
			if (whiteBoard[origonalX + x][origonalY + y] != '0')
			{
				moves[origonalX + x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY + y < BOARDSIZE && blackBoard[origonalX - x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX - x][origonalY + y] == '0' && whiteBoard[origonalX - x][origonalY + y] == '0')
			{
				moves[origonalX - x][origonalY + y] = true;
			}
			if (whiteBoard[origonalX - x][origonalY + y] != '0')
			{
				moves[origonalX - x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY - y >= 0 && blackBoard[origonalX - x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX - x][origonalY - y] == '0' && whiteBoard[origonalX - x][origonalY - y] == '0')
			{
				moves[origonalX - x][origonalY - y] = true;
			}
			if (whiteBoard[origonalX - x][origonalY - y] != '0')
			{
				moves[origonalX - x][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX + x < BOARDSIZE
			&& origonalY - y >= 0 && blackBoard[origonalX + x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX + x][origonalY - y] == '0' && whiteBoard[origonalX + x][origonalY - y] == '0')
			{
				moves[origonalX + x][origonalY - y] = true;
			}
			if (whiteBoard[origonalX + x][origonalY - y] != '0')
			{
				moves[origonalX + x][origonalY - y] = true;
				enemy = true;
			}
		}
		break;
	case 'q': //=============================================================================
		enemy = false;
		for (int y = 1; origonalY + y < BOARDSIZE && blackBoard[origonalX][origonalY + y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY + y] == '0' && blackBoard[origonalX][origonalY + y] == '0')
			{
				moves[origonalX][origonalY + y] = true;
			}
			if (whiteBoard[origonalX][origonalY + y] != '0')
			{
				moves[origonalX][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int y = 1; origonalY - y >= 0 && blackBoard[origonalX][origonalY - y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY - y] == '0' && blackBoard[origonalX][origonalY - y] == '0')
			{
				moves[origonalX][origonalY - y] = true;
			}
			if (whiteBoard[origonalX][origonalY - y] != '0')
			{
				moves[origonalX][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX + x < BOARDSIZE && blackBoard[origonalX + x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX + x][origonalY] == '0' && blackBoard[origonalX + x][origonalY] == '0')
			{
				moves[origonalX + x][origonalY] = true;
			}
			if (whiteBoard[origonalX + x][origonalY] != '0')
			{
				moves[origonalX + x][origonalY] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX - x >= 0 && blackBoard[origonalX - x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX - x][origonalY] == '0' && blackBoard[origonalX - x][origonalY] == '0')
			{
				moves[origonalX - x][origonalY] = true;
			}
			if (whiteBoard[origonalX - x][origonalY] != '0')
			{
				moves[origonalX - x][origonalY] = true;
				enemy = true;
			}
		}


		enemy = false;
		for (int x = 1, y = 1; x + origonalX < BOARDSIZE
			&& origonalY + y < BOARDSIZE && blackBoard[origonalX + x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX + x][origonalY + y] == '0' && whiteBoard[origonalX + x][origonalY + y] == '0')
			{
				moves[origonalX + x][origonalY + y] = true;
			}
			if (whiteBoard[origonalX + x][origonalY + y] != '0')
			{
				moves[origonalX + x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY + y < BOARDSIZE && blackBoard[origonalX - x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX - x][origonalY + y] == '0' && whiteBoard[origonalX - x][origonalY + y] == '0')
			{
				moves[origonalX - x][origonalY + y] = true;
			}
			if (whiteBoard[origonalX - x][origonalY + y] != '0')
			{
				moves[origonalX - x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY - y >= 0 && blackBoard[origonalX - x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX - x][origonalY - y] == '0' && whiteBoard[origonalX - x][origonalY - y] == '0')
			{
				moves[origonalX - x][origonalY - y] = true;
			}
			if (whiteBoard[origonalX - x][origonalY - y] != '0')
			{
				moves[origonalX - x][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX + x < BOARDSIZE
			&& origonalY - y >= 0 && blackBoard[origonalX + x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (blackBoard[origonalX + x][origonalY - y] == '0' && whiteBoard[origonalX + x][origonalY - y] == '0')
			{
				moves[origonalX + x][origonalY - y] = true;
			}
			if (whiteBoard[origonalX + x][origonalY - y] != '0')
			{
				moves[origonalX + x][origonalY - y] = true;
				enemy = true;
			}
		}

		break;
	case 'k': //=============================================================================
		if (castleKingside)
		{
			moves[6][0] = true;
		}
		if (castleQueenside)
		{
			moves[2][0] = true;
		}

		if (blackBoard[origonalX - 1][origonalY + 1] == '0'
			&& origonalX - 1 >= 0 && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX - 1][origonalY + 1] = true;
		}
		if (blackBoard[origonalX][origonalY + 1] == '0'
			&& origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX][origonalY + 1] = true;
		}
		if (blackBoard[origonalX + 1][origonalY + 1] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY + 1] = true;
		}

		if (blackBoard[origonalX - 1][origonalY] == '0'
			&& origonalX - 1 >= 0)
		{
			moves[origonalX - 1][origonalY] = true;
		}
		if (blackBoard[origonalX + 1][origonalY] == '0'
			&& origonalX + 1 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY] = true;
		}

		if (blackBoard[origonalX - 1][origonalY - 1] == '0'
			&& origonalX - 1 >= 0 && origonalY - 1 >= 0)
		{
			moves[origonalX - 1][origonalY - 1] = true;
		}
		if (blackBoard[origonalX][origonalY - 1] == '0'
			&& origonalY - 1 >= 0)
		{
			moves[origonalX][origonalY - 1] = true;
		}
		if (blackBoard[origonalX + 1][origonalY - 1] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY - 1 >= 0)
		{
			moves[origonalX + 1][origonalY - 1] = true;
		}

		break;
	default: //=============================================================================

		break;
	}

}

int AI::findMoves()
{
	char takenPiece;
	int piece[2];
	int moveLocation = 0;
	int difference;

	for (int x = 0; x < AMOVESIZE; x++)
	{
		legalMoves[x] = 0;
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (blackBoard[x][y] != '0' && blackBoard[x][y] != 's' && blackBoard[x][y] != 'O')
			{
				for (int row = 0; row < BOARDSIZE; row++)
				{
					for (int col = 0; col < BOARDSIZE; col++)
					{
						moves[row][col] = false;
					}
				}
				piece[0] = x;
				piece[1] = y;
				AI::moveReset();
				AI::AIswitch(piece);
				AI::blackNoMoveInCheck(piece);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							legalMoves[moveLocation] = inX * 1000 + inY * 100 + x * 10 + y;
							moveLocation++;
						}
					}
				}
			}
		}
	}
	return moveLocation;
}

int AI::findWhiteMoves()
{
	char takenPiece;
	int piece[2];
	int moveLocation = 0;
	int difference;

	for (int x = 0; x < AMOVESIZE; x++)
	{
		whiteMoves[x] = 0;
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 's' && whiteBoard[x][y] != 'O')
			{
				for (int row = 0; row < BOARDSIZE; row++)
				{
					for (int col = 0; col < BOARDSIZE; col++)
					{
						moves[row][col] = false;
					}
				}
				piece[0] = x;
				piece[1] = y;
				AI::moveReset();
				AI::whiteSwitch(piece, false);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							whiteMoves[moveLocation] = inX * 1000 + inY * 100 + x * 10 + y;
							moveLocation++;
						}
					}
				}
			}
		}
	}
	return moveLocation;
}

void AI::moveReset()
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = 0;
		}
	}
}

void AI::whiteSwitch(int position[], bool castle)
{
	int origonalX = position[0];
	int origonalY = position[1];

	bool enemy = false;
	bool check = false;

	switch (whiteBoard[origonalX][origonalY])
	{
	case 'p': //=============================================================================
		if (origonalY != 0)
		{
			if (whiteBoard[origonalX + 1][origonalY - 1] == '0' && blackBoard[origonalX + 1][origonalY - 1] == '0')
			{
				moves[origonalX + 1][origonalY - 1] = true;
			}
			/*if (whiteBoard[origonalX + 1][origonalY - 1] == '0' && blackBoard[origonalX + 1][origonalY - 1] == '0'
			&& whiteBoard[origonalX + 2][origonalY - 2] == '0' && blackBoard[origonalX + 2][origonalY - 2] == '0'
			&& origonalY == 6)
			{
			moves[origonalX][origonalY - 2] = true;
			}*/

			if (blackBoard[origonalX][origonalY - 1] != '0')
			{
				moves[origonalX][origonalY - 1] = true;
			}
			if (blackBoard[origonalX + 1][origonalY] != '0')
			{
				moves[origonalX + 1][origonalY] = true;
			}
		}
		break;
	case 'r': //=============================================================================
		enemy = false;
		for (int y = 1; origonalY + y < BOARDSIZE && whiteBoard[origonalX][origonalY + y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY + y] == '0' && blackBoard[origonalX][origonalY + y] == '0')
			{
				moves[origonalX][origonalY + y] = true;
			}
			if (blackBoard[origonalX][origonalY + y] != '0')
			{
				moves[origonalX][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int y = 1; origonalY - y >= 0 && whiteBoard[origonalX][origonalY - y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY - y] == '0' && blackBoard[origonalX][origonalY - y] == '0')
			{
				moves[origonalX][origonalY - y] = true;
			}
			if (blackBoard[origonalX][origonalY - y] != '0')
			{
				moves[origonalX][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX + x < BOARDSIZE && whiteBoard[origonalX + x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX + x][origonalY] == '0' && blackBoard[origonalX + x][origonalY] == '0')
			{
				moves[origonalX + x][origonalY] = true;
			}
			if (blackBoard[origonalX + x][origonalY] != '0')
			{
				moves[origonalX + x][origonalY] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX - x >= 0 && whiteBoard[origonalX - x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX - x][origonalY] == '0' && blackBoard[origonalX - x][origonalY] == '0')
			{
				moves[origonalX - x][origonalY] = true;
			}
			if (blackBoard[origonalX - x][origonalY] != '0')
			{
				moves[origonalX - x][origonalY] = true;
				enemy = true;
			}
		}

		break;
	case 'n': //=============================================================================
		if (whiteBoard[origonalX + 2][origonalY + 1] == '0'
			&& origonalX + 2 < BOARDSIZE && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX + 2][origonalY + 1] = true;
		}
		if (whiteBoard[origonalX + 1][origonalY + 2] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY + 2 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY + 2] = true;
		}
		if (whiteBoard[origonalX - 1][origonalY + 2] == '0'
			&& origonalX - 1 >= 0 && origonalY + 2 < BOARDSIZE)
		{
			moves[origonalX - 1][origonalY + 2] = true;
		}
		if (whiteBoard[origonalX - 2][origonalY + 1] == '0'
			&& origonalX - 2 >= 0 && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX - 2][origonalY + 1] = true;
		}

		if (whiteBoard[origonalX + 2][origonalY - 1] == '0'
			&& origonalX + 2 < BOARDSIZE && origonalY - 1 >= 0)
		{
			moves[origonalX + 2][origonalY - 1] = true;
		}
		if (whiteBoard[origonalX + 1][origonalY - 2] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY - 2 >= 0)
		{
			moves[origonalX + 1][origonalY - 2] = true;
		}
		if (whiteBoard[origonalX - 1][origonalY - 2] == '0'
			&& origonalX - 1 >= 0 && origonalY - 2 >= 0)
		{
			moves[origonalX - 1][origonalY - 2] = true;
		}
		if (whiteBoard[origonalX - 2][origonalY - 1] == '0'
			&& origonalX - 2 >= 0 && origonalY - 1 >= 0)
		{
			moves[origonalX - 2][origonalY - 1] = true;
		}
		break;
	case 'b': //=============================================================================
		enemy = false;
		for (int x = 1, y = 1; x + origonalX < BOARDSIZE
			&& origonalY + y < BOARDSIZE && whiteBoard[origonalX + x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX + x][origonalY + y] == '0' && blackBoard[origonalX + x][origonalY + y] == '0')
			{
				moves[origonalX + x][origonalY + y] = true;
			}
			if (blackBoard[origonalX + x][origonalY + y] != '0')
			{
				moves[origonalX + x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY + y < BOARDSIZE && whiteBoard[origonalX - x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX - x][origonalY + y] == '0' && blackBoard[origonalX - x][origonalY + y] == '0')
			{
				moves[origonalX - x][origonalY + y] = true;
			}
			if (blackBoard[origonalX - x][origonalY + y] != '0')
			{
				moves[origonalX - x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY - y >= 0 && whiteBoard[origonalX - x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX - x][origonalY - y] == '0' && blackBoard[origonalX - x][origonalY - y] == '0')
			{
				moves[origonalX - x][origonalY - y] = true;
			}
			if (blackBoard[origonalX - x][origonalY - y] != '0')
			{
				moves[origonalX - x][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX + x < BOARDSIZE
			&& origonalY - y >= 0 && whiteBoard[origonalX + x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX + x][origonalY - y] == '0' && blackBoard[origonalX + x][origonalY - y] == '0')
			{
				moves[origonalX + x][origonalY - y] = true;
			}
			if (blackBoard[origonalX + x][origonalY - y] != '0')
			{
				moves[origonalX + x][origonalY - y] = true;
				enemy = true;
			}
		}
		break;
	case 'q': //=============================================================================
		enemy = false;
		for (int y = 1; origonalY + y < BOARDSIZE && whiteBoard[origonalX][origonalY + y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY + y] == '0' && blackBoard[origonalX][origonalY + y] == '0')
			{
				moves[origonalX][origonalY + y] = true;
			}
			if (blackBoard[origonalX][origonalY + y] != '0')
			{
				moves[origonalX][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int y = 1; origonalY - y >= 0 && whiteBoard[origonalX][origonalY - y] == '0' && enemy == false; y++)
		{
			if (whiteBoard[origonalX][origonalY - y] == '0' && blackBoard[origonalX][origonalY - y] == '0')
			{
				moves[origonalX][origonalY - y] = true;
			}
			if (blackBoard[origonalX][origonalY - y] != '0')
			{
				moves[origonalX][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX + x < BOARDSIZE && whiteBoard[origonalX + x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX + x][origonalY] == '0' && blackBoard[origonalX + x][origonalY] == '0')
			{
				moves[origonalX + x][origonalY] = true;
			}
			if (blackBoard[origonalX + x][origonalY] != '0')
			{
				moves[origonalX + x][origonalY] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1; origonalX - x >= 0 && whiteBoard[origonalX - x][origonalY] == '0' && enemy == false; x++)
		{
			if (whiteBoard[origonalX - x][origonalY] == '0' && blackBoard[origonalX - x][origonalY] == '0')
			{
				moves[origonalX - x][origonalY] = true;
			}
			if (blackBoard[origonalX - x][origonalY] != '0')
			{
				moves[origonalX - x][origonalY] = true;
				enemy = true;
			}
		}


		enemy = false;
		for (int x = 1, y = 1; x + origonalX < BOARDSIZE
			&& origonalY + y < BOARDSIZE && whiteBoard[origonalX + x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX + x][origonalY + y] == '0' && blackBoard[origonalX + x][origonalY + y] == '0')
			{
				moves[origonalX + x][origonalY + y] = true;
			}
			if (blackBoard[origonalX + x][origonalY + y] != '0')
			{
				moves[origonalX + x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY + y < BOARDSIZE && whiteBoard[origonalX - x][origonalY + y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX - x][origonalY + y] == '0' && blackBoard[origonalX - x][origonalY + y] == '0')
			{
				moves[origonalX - x][origonalY + y] = true;
			}
			if (blackBoard[origonalX - x][origonalY + y] != '0')
			{
				moves[origonalX - x][origonalY + y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX - x >= 0
			&& origonalY - y >= 0 && whiteBoard[origonalX - x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX - x][origonalY - y] == '0' && blackBoard[origonalX - x][origonalY - y] == '0')
			{
				moves[origonalX - x][origonalY - y] = true;
			}
			if (blackBoard[origonalX - x][origonalY - y] != '0')
			{
				moves[origonalX - x][origonalY - y] = true;
				enemy = true;
			}
		}
		enemy = false;
		for (int x = 1, y = 1; origonalX + x < BOARDSIZE
			&& origonalY - y >= 0 && whiteBoard[origonalX + x][origonalY - y] == '0'
			&& enemy == false; x++, y++)
		{
			if (whiteBoard[origonalX + x][origonalY - y] == '0' && blackBoard[origonalX + x][origonalY - y] == '0')
			{
				moves[origonalX + x][origonalY - y] = true;
			}
			if (blackBoard[origonalX + x][origonalY - y] != '0')
			{
				moves[origonalX + x][origonalY - y] = true;
				enemy = true;
			}
		}

		break;
	case 'k': //=============================================================================

		if (whiteBoard[origonalX - 1][origonalY + 1] == '0'
			&& origonalX - 1 >= 0 && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX - 1][origonalY + 1] = true;
		}
		if (whiteBoard[origonalX][origonalY + 1] == '0'
			&& origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX][origonalY + 1] = true;
		}
		if (whiteBoard[origonalX + 1][origonalY + 1] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY + 1 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY + 1] = true;
		}

		if (whiteBoard[origonalX - 1][origonalY] == '0'
			&& origonalX - 1 >= 0)
		{
			moves[origonalX - 1][origonalY] = true;
		}
		if (whiteBoard[origonalX + 1][origonalY] == '0'
			&& origonalX + 1 < BOARDSIZE)
		{
			moves[origonalX + 1][origonalY] = true;
		}

		if (whiteBoard[origonalX - 1][origonalY - 1] == '0'
			&& origonalX - 1 >= 0 && origonalY - 1 >= 0)
		{
			moves[origonalX - 1][origonalY - 1] = true;
		}
		if (whiteBoard[origonalX][origonalY - 1] == '0'
			&& origonalY - 1 >= 0)
		{
			moves[origonalX][origonalY - 1] = true;
		}
		if (whiteBoard[origonalX + 1][origonalY - 1] == '0'
			&& origonalX + 1 < BOARDSIZE && origonalY - 1 >= 0)
		{
			moves[origonalX + 1][origonalY - 1] = true;
		}

		break;
	default: //=============================================================================

		break;
	}
}







