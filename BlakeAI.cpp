#include "BlakeAI.h"

BlakeAI::BlakeAI()
{

}

void BlakeAI::input(char whiteBoard[10][10], char blackBoard[10][10])
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

int BlakeAI::move()
{

	int position[2];
	int location[2];
	int best = -99999;
	int numBest = 0;

	myMove bestMoves[200];

	int moveNum = findMoves();
	char takenPiece;

	for (int x = 0; x < moveNum; x++)
	{
		avialableMoves[x].move = legalMoves[x];
	}

	for (int x = 0; x < moveNum; x++)
	{
		position[0] = avialableMoves[x].move / 1000;
		position[1] = (avialableMoves[x].move - position[0] * 1000) / 100;
		location[0] = (avialableMoves[x].move - position[0] * 1000 - position[1] * 100) / 10;
		location[1] = avialableMoves[x].move % 10;

		takenPiece = blackBoard[position[0]][position[1]];
		whiteBoard[position[0]][position[1]] = whiteBoard[location[0]][location[1]];
		blackBoard[position[0]][position[1]] = '0';
		whiteBoard[location[0]][location[1]] = '0';

		avialableMoves[x].score = countEmUp();

		blackBoard[position[0]][position[1]] = takenPiece;
		whiteBoard[location[0]][location[1]] = whiteBoard[position[0]][position[1]];
		whiteBoard[position[0]][position[1]] = '0';
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

int BlakeAI::countEmUp()
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

	int score = black - white;

	if (blackCheck())
	{
		score += 20;
	}
	if (blackMate())
	{
		score += 9000;
	}

	return score;
}

void BlakeAI::blackNoMoveInCheck(int position[])
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

void BlakeAI::whiteNoMoveInCheck(int position[])
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
				takenPiece = blackBoard[x][y];
				whiteBoard[x][y] = whiteBoard[position[0]][position[1]];
				blackBoard[x][y] = '0';
				whiteBoard[position[0]][position[1]] = '0';
				if (whiteCheck() == true)
				{
					legalMoves[x][y] = false;
				}
				blackBoard[x][y] = takenPiece;
				whiteBoard[position[0]][position[1]] = whiteBoard[x][y];
				whiteBoard[x][y] = '0';
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

bool BlakeAI::blackCheck()
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

bool BlakeAI::whiteCheck()
{
	bool legalMoves[10][10];
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			legalMoves[x][y] = moves[x][y];
		}
	}

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
			if (whiteBoard[x][y] == 'k')
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
			if (blackBoard[x][y] != '0')
			{
				position[0] = x;
				position[1] = y;
				BlakeAIswitch(position);
			}
		}
	}

	if (moves[KingX][KingY] == true)
	{
		moveReset();
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = legalMoves[x][y];
			}
		}
		return true;
	}
	moveReset();
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
	return false;
}

bool BlakeAI::blackMate()
{
	int position[2];
	char piece;
	bool legalMoves[10][10];
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
			if (blackBoard[x][y] != '0')
			{
				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						for (int x = 0; x < BOARDSIZE; x++)
						{
							for (int y = 0; y < BOARDSIZE; y++)
							{
								moves[x][y] = false;
							}
						}
						position[0] = x;
						position[1] = y;
						BlakeAIswitch(position);
						if (moves[inX][inY])
						{
							blackBoard[inX][inY] = blackBoard[x][y];
							blackBoard[x][y] = '0';
							piece = whiteBoard[inX][inY];
							whiteBoard[inX][inY] = '0';

							if (!blackCheck())
							{
								blackBoard[x][y] = blackBoard[inX][inY];
								blackBoard[inX][inY] = '0';
								whiteBoard[inX][inY] = piece;
								for (int x = 0; x < BOARDSIZE; x++)
								{
									for (int y = 0; y < BOARDSIZE; y++)
									{
										moves[x][y] = legalMoves[x][y];
									}
								}
								return false;
							}
							blackBoard[x][y] = blackBoard[inX][inY];
							blackBoard[inX][inY] = '0';
							whiteBoard[inX][inY] = piece;
						}
					}
				}
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
	return true;
}

void BlakeAI::BlakeAIswitch(int position[])
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

int BlakeAI::findMoves()
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
				BlakeAI::moveReset();
				BlakeAI::BlakeAIswitch(piece);
				BlakeAI::blackNoMoveInCheck(piece);

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

int BlakeAI::findWhiteMoves()
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
				BlakeAI::moveReset();
				BlakeAI::whiteSwitch(piece, false);
				whiteNoMoveInCheck(piece);

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

void BlakeAI::moveReset()
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = 0;
		}
	}
}

void BlakeAI::whiteSwitch(int position[], bool castle)
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

void BlakeAI::calcAverage()
{
	int sumWhite = 0;
	int sumNext = 0;

	for (int x = 0; x < AMOVESIZE; x++)
	{
		if (avialableMoves[x].totalNextMoves != 0 && avialableMoves[x].totalWhiteMoves != 0)
		{
			for (int y = 0; y < avialableMoves[x].totalWhiteMoves; y++)
			{
				//sumWhite = sumWhite + avialableMoves[x].scoreAfterWhiteMove[y];

			}


			for (int y = 0; y < avialableMoves[x].totalNextMoves; y++)
			{
				//sumNext = sumNext + avialableMoves[x].ScoreAfterAll[y];

			}


			avialableMoves[x].averageScore = (sumNext + sumWhite) / (avialableMoves[x].totalNextMoves + avialableMoves[x].totalWhiteMoves);
		}
	}
}




//int move = -1;
//int piece;
//int position[2];
//int location[2];
//bool legal = false;
//bool oneIsThere = false;
//while (oneIsThere == false)
//{
//	piece = BlakeAI::rand_lim(99);
//	position[0] = piece % 10;
//	position[1] = piece / 10;
//
//	if (blackBoard[position[0]][position[1]] != '0' && blackBoard[position[0]][position[1]] != 's' && blackBoard[position[0]][position[1]] != 'O')
//	{
//		BlakeAI::BlakeAIswitch(position);
//		for (int x = 0; x < BOARDSIZE; x++)
//		{
//			for (int y = 0; y < BOARDSIZE; y++)
//			{
//				if (moves[x][y] == true)
//				{
//					oneIsThere = true;
//				}
//			}
//		}
//	}
//}
//
//while (legal == false)
//{
//	piece = BlakeAI::rand_lim(100);
//	location[0] = piece % 10;
//	location[1] = piece / 10;
//
//	if (moves[location[0]][location[1]])
//	{
//		legal = true;
//	}
//}
//
//move = 1000 * location[0] + 100 * location[1] + 10 * position[0] + position[1];
//return move;
