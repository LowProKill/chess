#include "minimax.h"

void minimaxAI::init(int aiPlayer)
{

}

int minimaxAI::finalMove(char whiteBoard[10][10], char blackBoard[10][10], bool player)
{
	int position[2];
	int location[2];
	int count = 0;
	char takenPiece;
	bool moves[10][10] = {};

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			wBoard[x][y] = whiteBoard[x][y];
			bBoard[x][y] = blackBoard[x][y];
		}
	}

	theMove goodMoves[200];
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (player)
			{
				position[0] = x;
				position[1] = y;
				whiteMoves(position, whiteBoard, blackBoard, moves);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							location[0] = inX;
							location[1] = inY;
							takenPiece = bBoard[position[0]][position[1]];
							wBoard[position[0]][position[1]] = wBoard[location[0]][location[1]];
							bBoard[position[0]][position[1]] = '0';
							wBoard[location[0]][location[1]] = '0';

							//goodMoves[count] = makeTheMove(wBoard, bBoard, abs(player - 1), 0);
							goodMoves[count].move[0] = inX;
							goodMoves[count].move[1] = inY;
							goodMoves[count].move[2] = x;
							goodMoves[count].move[3] = y;
							
							count++;

							bBoard[position[0]][position[1]] = takenPiece;
							wBoard[location[0]][location[1]] = wBoard[position[0]][position[1]];
							wBoard[position[0]][position[1]] = '0';
						}
					}

				}
			}
			else
			{
				position[0] = x;
				position[1] = y;
				blackMoves(position, whiteBoard, blackBoard, moves);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							location[0] = inX;
							location[1] = inY;
							takenPiece = wBoard[position[0]][position[1]];
							bBoard[position[0]][position[1]] = bBoard[location[0]][location[1]];
							wBoard[position[0]][position[1]] = '0';
							bBoard[location[0]][location[1]] = '0';

							//goodMoves[count] = makeTheMove(wBoard, bBoard, abs(player - 1), 0);
							goodMoves[count].move[0] = inX;
							goodMoves[count].move[1] = inY;
							goodMoves[count].move[2] = x;
							goodMoves[count].move[3] = y;
							goodMoves[count].count(wBoard, bBoard, whiteCheck(wBoard, bBoard), whiteMate(wBoard, bBoard), player);
							count++;

							wBoard[position[0]][position[1]] = takenPiece;
							bBoard[location[0]][location[1]] = bBoard[position[0]][position[1]];
							bBoard[position[0]][position[1]] = '0';

						}
					}
				}
			}

		}
	}

	int best = -999999;
	int bestLocation = 0;
	int numBest = 0;
	int newCount = 0;
	int theBestMove;
	theMove bestMove[50];

	for (int x = 0; x < count; x++)
	{
		if (goodMoves[x].score > best)
		{
			best = goodMoves[x].score;
			numBest = 1;
		}
		if (goodMoves[x].score == best)
		{
			numBest++;
		}
	}

	for (int x = 0; x < count; x++)
	{
		if (goodMoves[x].score == best)
		{
			bestMove[newCount] = goodMoves[x];
			newCount++;
		}
	}
	newCount--;
	srand(time(NULL));
	if (newCount == 0)
	{
		srand(time(NULL));
		bestLocation = rand() % count;
		theBestMove = goodMoves[bestLocation].move[0] * 1000 + goodMoves[bestLocation].move[1] * 100 + goodMoves[bestLocation].move[2] * 10 + goodMoves[bestLocation].move[3];
		return theBestMove;
	}
	bestLocation = rand() % newCount;
	theBestMove = bestMove[bestLocation].move[0] * 1000 + bestMove[bestLocation].move[1] * 100 + bestMove[bestLocation].move[2] * 10 + bestMove[bestLocation].move[3];
	return theBestMove;
}

theMove minimaxAI::makeTheMove(char whiteBoard[10][10], char blackBoard[10][10], bool player, int depth)
{
	theMove move;
	depth++;

	int position[2];
	int location[2];
	int count = 0;
	char takenPiece;
	bool moves[10][10] = {};

	char inWBoard[10][10];
	char inBBoard[10][10];


	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			inWBoard[x][y] = whiteBoard[x][y];
			inBBoard[x][y] = blackBoard[x][y];
		}
	}


	if (depth > MAXDEPTH || blackMate(inWBoard, inBBoard) || whiteMate(inWBoard, inBBoard))
	{
		if (player)
		{
			move.count(inWBoard, inBBoard, blackCheck(inWBoard, inBBoard), blackMate(inWBoard, inBBoard), player);
			return move;
		}
		else
		{
			move.count(inWBoard, inBBoard, whiteCheck(inWBoard, inBBoard), whiteMate(inWBoard, inBBoard), player);
			return move;
		}
	}
	
	theMove goodMoves[50];

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (player)
			{
				position[0] = x;
				position[1] = y;
				whiteMoves(position, whiteBoard, blackBoard, moves);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							if (count < 50)
							{
								location[0] = inX;
								location[1] = inY;
								takenPiece = bBoard[position[0]][position[1]];
								inWBoard[position[0]][position[1]] = inWBoard[location[0]][location[1]];
								inBBoard[position[0]][position[1]] = '0';
								inWBoard[location[0]][location[1]] = '0';

								goodMoves[count] = makeTheMove(wBoard, bBoard, abs(player - 1), depth);
								goodMoves[count].move[0] = inX;
								goodMoves[count].move[1] = inY;
								goodMoves[count].move[2] = x;
								goodMoves[count].move[3] = y;
								count++;

								inBBoard[position[0]][position[1]] = takenPiece;
								inWBoard[location[0]][location[1]] = inWBoard[position[0]][position[1]];
								inWBoard[position[0]][position[1]] = '0';
							}
						}
					}

				}
			}
			else
			{
				position[0] = x;
				position[1] = y;
				blackMoves(position, whiteBoard, blackBoard, moves);

				for (int inX = 0; inX < BOARDSIZE; inX++)
				{
					for (int inY = 0; inY < BOARDSIZE; inY++)
					{
						if (moves[inX][inY])
						{
							if (count < 50)
							{
								location[0] = inX;
								location[1] = inY;
								takenPiece = inWBoard[position[0]][position[1]];
								inBBoard[position[0]][position[1]] = inBBoard[location[0]][location[1]];
								inBBoard[position[0]][position[1]] = '0';
								inBBoard[location[0]][location[1]] = '0';

								goodMoves[count] = makeTheMove(wBoard, bBoard, abs(player - 1), depth);
								goodMoves[count].move[0] = inX;
								goodMoves[count].move[1] = inY;
								goodMoves[count].move[2] = x;
								goodMoves[count].move[3] = y;
								count++;

								inWBoard[position[0]][position[1]] = takenPiece;
								inBBoard[location[0]][location[1]] = inBBoard[position[0]][position[1]];
								inBBoard[position[0]][position[1]] = '0';
							}
						}
					}
				}
			}
		}
	}

	int best = -999999;
	int bestLocation = 0;
	int numBest = 0;
	int newCount = 0;
	theMove bestMove[50];

	for (int x = 0; x < count; x++)
	{
		if (goodMoves[x].score > best)
		{
			best = goodMoves[x].score;
			numBest = 1;
		}
		if (goodMoves[x].score == best)
		{
			numBest++;
		}
	}

	for (int x = 0; x < count; x++)
	{
		if (goodMoves[x].score == best)
		{
			bestMove[newCount] = goodMoves[x];
			newCount++;
		}
	}
	newCount--;
	srand(time(NULL));
	if (newCount == 0)
	{
		srand(time(NULL));
		bestLocation = rand() % count;
		return goodMoves[bestLocation];
	}
	bestLocation = rand() % newCount;
	return bestMove[bestLocation];
}

void minimaxAI::blackMoves(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10])
{
	int origonalX = position[0];
	int origonalY = position[1];

	bool enemy = false;
	bool check = false;

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

void minimaxAI::whiteMoves(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10])
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

void minimaxAI::moveReset()
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			//moves[x][y] = 0;
		}
	}
}

bool minimaxAI::whiteCheck(char whiteBoard[10][10], char blackBoard[10][10])
{
	bool legalMoves[10][10];
	bool moves[10][10] = {};
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
				blackMoves(position, whiteBoard, blackBoard, moves);
			}
		}
	}

	if (moves[KingX][KingY] == true)
	{
		minimaxAI::moveReset();
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = legalMoves[x][y];
			}
		}
		return true;
	}
	minimaxAI::moveReset();
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
	return false;
}

bool minimaxAI::blackCheck(char whiteBoard[10][10], char blackBoard[10][10])
{
	bool legalMoves[10][10];
	bool moves[10][10] = {};
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
				whiteMoves(position, whiteBoard, blackBoard, moves);
			}
		}
	}

	if (moves[KingX][KingY] == true)
	{
		minimaxAI::moveReset();
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = legalMoves[x][y];
			}
		}
		return true;
	}
	minimaxAI::moveReset();
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
	return false;
}

void minimaxAI::whiteNoMoveInCheck(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10])
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
				if (whiteCheck(whiteBoard, blackBoard) == true)
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

void minimaxAI::blackNoMoveInCheck(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10])
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
				if (blackCheck(whiteBoard, blackBoard) == true)
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

bool minimaxAI::whiteMate(char whiteBoard[10][10], char blackBoard[10][10])
{
	int position[2];
	char piece;
	bool legalMoves[10][10];
	bool moves[10][10] = {};
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
			if (whiteBoard[x][y] != '0')
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
						whiteMoves(position, whiteBoard, blackBoard, moves);
						if (moves[inX][inY])
						{
							whiteBoard[inX][inY] = whiteBoard[x][y];
							whiteBoard[x][y] = '0';
							piece = blackBoard[inX][inY];
							blackBoard[inX][inY] = '0';

							if (!whiteCheck(whiteBoard, blackBoard))
							{
								whiteBoard[x][y] = whiteBoard[inX][inY];
								whiteBoard[inX][inY] = '0';
								blackBoard[inX][inY] = piece;

								for (int x = 0; x < BOARDSIZE; x++)
								{
									for (int y = 0; y < BOARDSIZE; y++)
									{
										moves[x][y] = legalMoves[x][y];
									}
								}
								return false;
							}
							whiteBoard[x][y] = whiteBoard[inX][inY];
							whiteBoard[inX][inY] = '0';
							blackBoard[inX][inY] = piece;
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

bool minimaxAI::blackMate(char whiteBoard[10][10], char blackBoard[10][10])
{
	int position[2];
	char piece;
	bool legalMoves[10][10];
	bool moves[10][10] = {};
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
						blackMoves(position, whiteBoard, blackBoard, moves);
						if (moves[inX][inY])
						{
							blackBoard[inX][inY] = blackBoard[x][y];
							blackBoard[x][y] = '0';
							piece = whiteBoard[inX][inY];
							whiteBoard[inX][inY] = '0';

							if (!blackCheck(whiteBoard, blackBoard))
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
