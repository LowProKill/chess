#pragma once
#include <random>
#include <iostream>
#include <time.h>

class BlakeAI
{
public:
	BlakeAI();

	void input(char whiteBoard[10][10], char blackBoard[10][10]);

	int move();

private:
	int countEmUp();

	void blackNoMoveInCheck(int position[]);

	void whiteNoMoveInCheck(int Position[]);

	bool blackCheck();

	bool whiteCheck();

	bool blackMate();

	void BlakeAIswitch(int position[]);

	void whiteSwitch(int position[], bool castle);

	void moveReset();

	int findMoves();

	int findWhiteMoves();

	void calcAverage();

	const int BOARDSIZE = 10;
	const int AMOVESIZE = 200;

	char whiteBoard[10][10] = {};
	char blackBoard[10][10] = {};

	bool moves[10][10] = {};

	
	

	int pawnStat = 10;
	int knightStat = 30;
	int bishopStat = 30;
	int rookStat = 50;
	int queenStat = 90;
	int kingStat = 900;

	int maxDepth = 50;

	struct myMove {
		int move;

		int score;
		//int scoreAfterWhiteMove[200];
		//int ScoreAfterAll[1000];
		int averageScore;
		int totalWhiteMoves;
		int totalNextMoves;
	};

	myMove avialableMoves[200];
	int whiteMoves[200];
	int legalMoves[200];
};