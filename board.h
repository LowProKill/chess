#pragma once
#include <Windows.h>
#include <iostream>
#include "display.h"
#include "AI.h"
#include "BlakeAI.h"
#include "minimax.h"
#include "saveGame.h"


const int BOARDSIZE = 10;

static char whiteBoard[BOARDSIZE][BOARDSIZE];
static char blackBoard[BOARDSIZE][BOARDSIZE];

class Board
{
public:
	Board();

	void reset();

	bool whiteCheck();

	bool blackCheck();

	bool whiteMove();

	bool blackMove();

	bool AImove();

	bool BlakeAImove();

	void draw(bool ai = false);

	int menu();

	int gameMenu(bool ai, bool turn);

	void localGame(bool whoseTurn = false);

	void singlePlayerGame();

	void BlakevsAI();

	bool whiteMate();

	bool blackMate();

	bool someoneInCheck();

	void whiteNoMoveInCheck(int position[]);

	void blackNoMoveInCheck(int position[]);

	void moveReset();

	void whiteSwitch(int position[], bool castle = true);

	void blackSwitch(int position[], bool castle = true);

	bool makeTheMove(int position[], int location[], bool whites, bool ai = false);

	void updatePrevious(int position[], int location[]);

	sf::Clock clock;
	sf::Time elapsed1;

	

	Display display;
	AI ai;
	saveGame saves;
	//BlakeAI blakeAI;
	//minimaxAI minAI;

	bool moves[BOARDSIZE][BOARDSIZE] = {};

	bool previousMove[BOARDSIZE][BOARDSIZE] = {};

	bool isAi = false;
	bool leftWhiteRook = true;
	bool rightWhiteRook = true;
	bool whiteKing = true;

	bool leftBlackRook = true;
	bool rightBlackRook = true;
	bool blackKing = true;

	bool castleQueenside = false;
	bool castleKingside = false;

	bool gameMode;

	int spLocation[2] = { 3, 3 };
	int mpLocation[2] = { 5, 6 };
	int quitLocation[2] = { 9, 9 };
	int saveLocation[2] = { 2, 7 };
	int loadGame[2] = { 4, 7 };

	bool starWars = false;

};