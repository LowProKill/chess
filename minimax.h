#pragma once
#include <cmath>
#include <time.h>

//const int BOARDSIZE = 10;

struct theMove
{
	theMove() {};
	theMove(int Score) : score(Score) {}

	int move[4] = { 0, 0, 0, 0 };
	int score;

	int BOARDSIZE = 10;

	int pawnStat = 10;
	int knightStat = 30;
	int bishopStat = 30;
	int rookStat = 50;
	int queenStat = 90;
	int kingStat = 900;

	void count(char wBoard[10][10], char bBoard[10][10], bool check, bool mate, bool player)
	{
		int white = 0;
		int black = 0;

		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				if (wBoard[x][y] != '0' && wBoard[x][y] != 'O')
				{
					switch (wBoard[x][y])
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
				if (bBoard[x][y] != '0' && bBoard[x][y] != 'O')
				{
					switch (bBoard[x][y])
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
		if (player)
		{
			score = black - white;
		}
		else
		{
			score = white - black;
		}

		if (check)
		{
			score += 20;
		}
		if (mate)
		{
			score += 9000;
		}
	};

};

class minimaxAI
{
public:

	minimaxAI() {}

	void init(int aiPlayer);

	int finalMove(char wBoard[10][10], char bBoard[10][10], bool player);

private:

	theMove makeTheMove(char wBoard[10][10], char bBoard[10][10], bool player, int depth);

	void blackMoves(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10]);

	void whiteMoves(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10]);

	void moveReset();

	bool whiteCheck(char whiteBoard[10][10], char blackBoard[10][10]);

	bool blackCheck(char whiteBoard[10][10], char blackBoard[10][10]);

	bool whiteMate(char whiteBoard[10][10], char blackBoard[10][10]);

	bool blackMate(char whiteBoard[10][10], char blackBoard[10][10]);

	void blackNoMoveInCheck(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10]);

	void whiteNoMoveInCheck(int position[], char whiteBoard[10][10], char blackBoard[10][10], bool moves[10][10]);

	char wBoard[10][10];
	char bBoard[10][10];

	bool LegalMoves[10][10];

	int BOARDSIZE = 10;
	int MAXDEPTH = 0;



};