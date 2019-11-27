#pragma once
#include <random>
#include <iostream>
#include <time.h>
#include "Moves.h"

class AI
{
public:
	AI();

	void input(char whiteBoard[10][10], char blackBoard[10][10]);

	int move();

private:
	int initialize();

	int countEmUp();

	void blackNoMoveInCheck(int position[]);

	bool blackCheck();

	void AIswitch(int position[]);

	void whiteSwitch(int position[], bool castle);

	void moveReset();

	int findMoves();

	int findWhiteMoves();

	const int BOARDSIZE = 10;
	const int AMOVESIZE = 300;
	int maxDepth = 50;

	char whiteBoard[10][10] = {};
	char blackBoard[10][10] = {};

	bool moves[10][10] = {};




	int pawnStat = 10;
	int knightStat = 30;
	int bishopStat = 30;
	int rookStat = 50;
	int queenStat = 90;
	int kingStat = 900;

	

	myMove avialableMoves[300];
	int whiteMoves[200];
	int legalMoves[200];
};



