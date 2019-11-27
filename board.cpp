#include "board.h"

Board::Board()
{
	gameMode = false;
	for (int X = 0; X < BOARDSIZE; X++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			whiteBoard[X][y] = '0';
			blackBoard[X][y] = '0';
		}
	}
	display.textures(false);

	whiteBoard[0][5] = whiteBoard[0][6]
		= whiteBoard[1][6] = whiteBoard[2][7]
		= whiteBoard[3][8] = whiteBoard[3][9]
		= whiteBoard[4][9] = whiteBoard[2][6]
		= whiteBoard[3][7] = 'p';

	whiteBoard[0][7] = whiteBoard[2][9] = 'n';

	whiteBoard[1][7] = whiteBoard[2][8] = 'r';

	whiteBoard[0][8] = whiteBoard[1][8] = 'b';

	whiteBoard[1][9] = 'q';

	whiteBoard[0][9] = 'k';


	blackBoard[5][0] = blackBoard[6][0]
		= blackBoard[6][1] = blackBoard[7][2]
		= blackBoard[8][3] = blackBoard[9][3]
		= blackBoard[9][4] = blackBoard[6][2]
		= blackBoard[7][3] = 'p';

	blackBoard[7][0] = blackBoard[9][2] = 'n';

	blackBoard[7][1] = blackBoard[8][2] = 'r';

	blackBoard[8][0] = blackBoard[8][1] = 'b';

	blackBoard[9][1] = 'q';

	blackBoard[9][0] = 'k';

	whiteBoard[0][0] = whiteBoard[1][0]
		= whiteBoard[0][1] = whiteBoard[1][1]
		= whiteBoard[2][0] = whiteBoard[0][2]
		= whiteBoard[9][9] = whiteBoard[8][9]
		= whiteBoard[9][8] = whiteBoard[8][8]
		= whiteBoard[7][9] = whiteBoard[9][7] = 'O';

	blackBoard[0][0] = blackBoard[1][0]
		= blackBoard[0][1] = blackBoard[1][1]
		= blackBoard[2][0] = blackBoard[0][2]
		= blackBoard[9][9] = blackBoard[8][9]
		= blackBoard[9][8] = blackBoard[8][8]
		= blackBoard[7][9] = blackBoard[9][7] = 'O';

	int whitePosition = 0;
	int blackPosition = 0;
}

void Board::reset()
{
	gameMode = false;
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			previousMove[x][y] = false;
		}
	}
	display.textures(false);
	
	for (int X = 0; X < BOARDSIZE; X++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			whiteBoard[X][y] = '0';
			blackBoard[X][y] = '0';
		}
	}

	whiteBoard[0][5] = whiteBoard[0][6]
		= whiteBoard[1][6] = whiteBoard[2][7]
		= whiteBoard[3][8] = whiteBoard[3][9]
		= whiteBoard[4][9] = whiteBoard[2][6]
		= whiteBoard[3][7] = 'p';

	whiteBoard[0][7] = whiteBoard[2][9] = 'n';

	whiteBoard[1][7] = whiteBoard[2][8] = 'r';

	whiteBoard[0][8] = whiteBoard[1][8] = 'b';

	whiteBoard[1][9] = 'q';

	whiteBoard[0][9] = 'k';


	blackBoard[5][0] = blackBoard[6][0]
		= blackBoard[6][1] = blackBoard[7][2]
		= blackBoard[8][3] = blackBoard[9][3]
		= blackBoard[9][4] = blackBoard[6][2]
		= blackBoard[7][3] = 'p';

	blackBoard[7][0] = blackBoard[9][2] = 'n';

	blackBoard[7][1] = blackBoard[8][2] = 'r';

	blackBoard[8][0] = blackBoard[8][1] = 'b';

	blackBoard[9][1] = 'q';

	blackBoard[9][0] = 'k';

	whiteBoard[0][0] = whiteBoard[1][0]
		= whiteBoard[0][1] = whiteBoard[1][1]
		= whiteBoard[2][0] = whiteBoard[0][2]
		= whiteBoard[9][9] = whiteBoard[8][9]
		= whiteBoard[9][8] = whiteBoard[8][8]
		= whiteBoard[7][9] = whiteBoard[9][7] = 'O';

	blackBoard[0][0] = blackBoard[1][0]
		= blackBoard[0][1] = blackBoard[1][1]
		= blackBoard[2][0] = blackBoard[0][2]
		= blackBoard[9][9] = blackBoard[8][9]
		= blackBoard[9][8] = blackBoard[8][8]
		= blackBoard[7][9] = blackBoard[9][7] = 'O';



	int whitePosition = 0;
	int blackPosition = 0;
}

int Board::menu()
{
	int click = 0;
	int position[2];

	display.clear();

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (previousMove[x][y])
			{
				display.input('M', x, y, 1);
			}
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 's' && whiteBoard[x][y] != 'O')
			{
				display.input(whiteBoard[x][y], x, y, true);
			}
			else if (blackBoard[x][y] != '0' && blackBoard[x][y] != 's' && blackBoard[x][y] != 'O')
			{
				display.input(blackBoard[x][y], x, y, false);
			}
			if (moves[x][y] == true)
			{
				display.input('A', x, y, true);
			}
		}
	}

	if (Board::someoneInCheck())
	{
		display.input('C', 8, 8, 1);
	}
	if (Board::whiteMate())
	{
		display.input('c', 9, 8, 1);
	}
	if (Board::blackMate())
	{
		display.input('c', 9, 8, 1);
	}

	display.input('S', spLocation[0], spLocation[1], true);
	display.input('E', spLocation[0] + 1, spLocation[1], true);
	display.input('L', mpLocation[0], mpLocation[1], true);
	display.input('E', mpLocation[0] + 1, mpLocation[1], true);
	display.input('Q', quitLocation[0], quitLocation[1], true);
	display.input('g', loadGame[0], loadGame[1], true);

	display.display();

	click = display.click();

	position[0] = click % 10;
	position[1] = click / 10;

	if (position[1] == spLocation[1] && (position[0] == spLocation[0] || position[0] == spLocation[0] + 1))
	{
		reset();
		isAi = true;
		singlePlayerGame();
		return 1;
	}

	else if (position[0] == loadGame[0] && position[1] == loadGame[1])
	{
		int where = saves.load(whiteBoard, blackBoard);
		if (where == 0)
		{
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
			std::cout << "Error! could not find file data/data/save.dat";
			return menu();
		}
		if (where == -1)
		{
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
			std::cout << "Error! file data/data/save.dat corupted";
			return menu();
		}
		else if (where == 11)
		{
			singlePlayerGame();
		}
		else if (where == 21)
		{
			localGame();
		}
		else if (where == 22)
		{
			localGame(true);
		}
		else return menu();
	}

	else if (position[1] == mpLocation[1] && (position[0] == mpLocation[0] || position[0] == mpLocation[0] + 1))
	{
		reset();
		isAi = false;
		localGame();
		return 1;
	}

	else if (position[0] == quitLocation[0] && position[1] == quitLocation[1])
	{
		throw 1;
	}
	return Board::menu();
}

int Board::gameMenu(bool ai, bool turn)
{
	int click = 0;
	int position[2];

	display.clear();

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (previousMove[x][y])
			{
				display.input('M', x, y, 1);
			}
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 's' && whiteBoard[x][y] != 'O')
			{
				display.input(whiteBoard[x][y], x, y, true);
			}
			else if (blackBoard[x][y] != '0' && blackBoard[x][y] != 's' && blackBoard[x][y] != 'O')
			{
				display.input(blackBoard[x][y], x, y, false);
			}
			if (moves[x][y] == true)
			{
				display.input('A', x, y, true);
			}
		}
	}

	if (Board::someoneInCheck())
	{
		display.input('C', 8, 8, 1);
	}

	display.input('R', spLocation[0], spLocation[1], true);
	display.input('m', mpLocation[0], mpLocation[1], true);
	display.input('Q', quitLocation[0], quitLocation[1], true);
	display.input('G', saveLocation[0], saveLocation[1], true);
	display.input('g', loadGame[0], loadGame[1], true);

	display.display();

	click = display.click();

	position[0] = click % 10;
	position[1] = click / 10;

	if (position[0] == spLocation[0] && position[1] == spLocation[1])
	{
		reset();
		
		return 1;
	}
	else if (position[0] == loadGame[0] && position[1] == loadGame[1])
	{
		int where = saves.load(whiteBoard, blackBoard);
		if (where == 0)
		{
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
			std::cout << "Error! could not find file data/data/save.dat";
			return menu();
		}
		else if (where == -1)
		{
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
			std::cout << "Error! file data/data/save.dat corupted";
			return menu();
		}
		else if (where == 11)
		{
			singlePlayerGame();
		}
		else if (where == 21)
		{
			localGame();
		}
		else if (where == 22)
		{
			localGame(true);
		}
		else return menu();
	}
	else if (position[0] == mpLocation[0] && position[1] == mpLocation[1])
	{
		return menu();
	}
	else if (position[0] == quitLocation[0] && position[1] == quitLocation[1])
	{
		throw 1;
	}
	else if (position[0] == saveLocation[0] && position[1] == saveLocation[1])
	{
		saves.save(whiteBoard, blackBoard, turn, ai);
	}
	else if (position[0] == 0 && position[1] == 0)
	{
		display.textures(starWars);
		if (starWars)
		{
			starWars = false;
		}
		else
		{
			starWars = true;
		}
		
		return gameMenu(ai, turn);
	}
	return 0;
}

void Board::localGame(bool whoseTurn)
{
	bool noNewGame = false;
	draw();
	while (true)
	{
		if (!whoseTurn)
		{
			sf::Clock clock;
			sf::Time elapsed1;
			draw();
			draw();
			if (whiteMate())
			{
				std::cout << "Black Wins!!!" << std::endl;
				display.click();
				menu();
				return;
			}
			if (whiteCheck())
			{
				std::cout << "White in Check" << std::endl;
			}

			noNewGame = whiteMove();
			if (!noNewGame)
			{
				return localGame();
			}

			draw();
		}
		whoseTurn = false;
		draw();
		if (blackMate())
		{
			std::cout << "White Wins!!!" << std::endl;
			display.click();
			menu();
			return;
		}
		if (blackCheck())
		{
			std::cout << "Black in Check" << std::endl;
		}

		noNewGame = blackMove();
		if (!noNewGame)
		{
			return localGame();
		}
	}
}

void Board::singlePlayerGame()
{
	bool noNewGame = false;
	draw(false);
	while (true)
	{
		sf::Clock clock;
		sf::Time elapsed1;
		draw(true);
		if (whiteMate())
		{
			std::cout << "Black Wins!!!" << std::endl;
			draw(true);
			display.click();
			menu();
			return;
		}
		if (whiteCheck())
		{
			std::cout << "White in Check" << std::endl;
		}

		noNewGame = whiteMove();
		if (!noNewGame)
		{
			return singlePlayerGame();
		}

		draw(true);
		if (blackMate())
		{
			std::cout << "White Wins!!!" << std::endl;
			draw();
			display.click();
			menu();
			return;
		}
		if (blackCheck())
		{
			std::cout << "Black in Check" << std::endl;
		}

		AImove();
	}
}

void Board::BlakevsAI()
{
	bool noNewGame = false;
	draw(false);
	while (true)
	{
		sf::Clock clock;
		sf::Time elapsed1;
		draw(true);
		if (whiteMate())
		{
			std::cout << "Black Wins!!!" << std::endl;
			draw(true);
			display.click();
			menu();
			return;
		}
		if (whiteCheck())
		{
			std::cout << "White in Check" << std::endl;
		}

		noNewGame = BlakeAImove();
		if (!noNewGame)
		{
			return singlePlayerGame();
		}

		draw(true);
		if (blackMate())
		{
			std::cout << "White Wins!!!" << std::endl;
			draw();
			display.click();
			menu();
			return;
		}
		if (blackCheck())
		{
			std::cout << "Black in Check" << std::endl;
		}

		AImove();
	}
}

bool Board::whiteCheck()
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

	int KingX = -1;
	int KingY = -1;

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
	if (KingX == -1)
	{
		return true;
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (blackBoard[x][y] != '0')
			{
				position[0] = x;
				position[1] = y;
				blackSwitch(position, 0);
			}
		}
	}

	if (moves[KingX][KingY] == true)
	{
		Board::moveReset();
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = legalMoves[x][y];
			}
		}
		return true;
	}
	Board::moveReset();
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
	return false;
}

bool Board::blackCheck()
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

	int KingX = -1;
	int KingY = -1;

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
	if (KingX == -1)
	{
		return true;
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
		Board::moveReset();
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = legalMoves[x][y];
			}
		}
		return true;
	}
	Board::moveReset();
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = legalMoves[x][y];
		}
	}
	return false;
}

bool Board::someoneInCheck()
{
	if (Board::whiteCheck() || Board::blackCheck())
	{
		return true;
	}
	return false;
}

void Board::whiteNoMoveInCheck(int position[])
{
	int legalMoves[BOARDSIZE][BOARDSIZE];
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

void Board::blackNoMoveInCheck(int position[])
{
	int legalMoves[BOARDSIZE][BOARDSIZE];
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

bool Board::whiteMate()
{
	if (!whiteCheck())
	{
		return false;
	}
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
						whiteSwitch(position);
						if (moves[inX][inY])
						{
							whiteBoard[inX][inY] = whiteBoard[x][y];
							whiteBoard[x][y] = '0';
							piece = blackBoard[inX][inY];
							blackBoard[inX][inY] = '0';

							if (!whiteCheck())
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

bool Board::blackMate()
{
	if (!blackCheck())
	{
		return false;
	}
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
						blackSwitch(position);
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

bool Board::whiteMove()
{
	bool whitePieceFound = false;
	char takenPiece;
	bool legalMoves[BOARDSIZE][BOARDSIZE];
	int click;
	int position[2];
	int location[2];
	bool legalMove = false;
	int responce = 0;

	while (whitePieceFound == false)
	{
		click = display.click();
		if (click == 99)
		{
			responce = gameMenu(isAi, true);
			if (responce == 1)
			{
				return false;
			}
			else
			{
				draw();
				return whiteMove();
			}
		}

		position[0] = click % 10;
		position[1] = click / 10;
		if (whiteBoard[position[0]][position[1]] != '0'
			&& whiteBoard[position[0]][position[1]] != 's'
			&& whiteBoard[position[0]][position[1]] != 'O')
		{
			whitePieceFound = true;
		}
	}

	Board::moveReset();
	Board::whiteSwitch(position, false);
	Board::whiteNoMoveInCheck(position);
	Board::draw();

	click = display.click();
	location[0] = click % 10;
	location[1] = click / 10;

	if (!Board::makeTheMove(location, position, true))
	{
		return false;
	}
	Board::moveReset();
	return true;
}

bool Board::makeTheMove(int position[], int location[], bool whites, bool ai)
{
	int click;
	char takenPiece;
	int responce;
	if (whites)
	{
		if (ai)
		{
			takenPiece = blackBoard[position[0]][position[1]];
			whiteBoard[position[0]][position[1]] = whiteBoard[location[0]][location[1]];
			blackBoard[position[0]][position[1]] = '0';
			whiteBoard[location[0]][location[1]] = '0';
			Board::updatePrevious(position, location);
			return true;
		}
		if (whiteBoard[position[0]][position[1]] != '0')
		{
			Board::moveReset();
			Board::whiteSwitch(position, false);
			Board::whiteNoMoveInCheck(position);
			Board::draw(ai);
			click = display.click();
			if (click == 99)
			{
				responce = gameMenu(isAi, true);
				if (responce == 1)
				{
					return false;
				}
			}

			location[0] = click % 10;
			location[1] = click / 10;
			return Board::makeTheMove(location, position, whites);
		}

		else if (moves[position[0]][position[1]])
		{
			takenPiece = blackBoard[position[0]][position[1]];
			whiteBoard[position[0]][position[1]] = whiteBoard[location[0]][location[1]];
			blackBoard[position[0]][position[1]] = '0';
			whiteBoard[location[0]][location[1]] = '0';
			if (whiteCheck() == true)
			{
				blackBoard[position[0]][position[1]] = takenPiece;
				whiteBoard[location[0]][location[1]] = whiteBoard[position[0]][position[1]];
				whiteBoard[position[0]][position[1]] = '0';
				std::cout << std::endl << "Move out of check" << std::endl;
				return Board::whiteMove();
			}
			Board::updatePrevious(position, location);
			return true;
		}
		
		else
		{
			Board::moveReset();
			Board::draw();
			return Board::whiteMove();
		}
	}
	else if (ai)
	{
		takenPiece = whiteBoard[position[0]][position[1]];
		blackBoard[position[0]][position[1]] = blackBoard[location[0]][location[1]];
		whiteBoard[position[0]][position[1]] = '0';
		blackBoard[location[0]][location[1]] = '0';
		Board::updatePrevious(position, location);
		return true;
	}
	else
	{
		if (blackBoard[position[0]][position[1]] != '0' && ai == false)
		{
			Board::moveReset();
			Board::blackSwitch(position, false);
			Board::blackNoMoveInCheck(position);
			Board::draw(ai);
			click = display.click();
			if (click == 99)
			{
				responce = gameMenu(false, false);
				if (responce == 1)
				{
					return false;
				}
			}
			location[0] = click % 10;
			location[1] = click / 10;
			return Board::makeTheMove(location, position, whites);
		}

		else if (moves[position[0]][position[1]])
		{
			takenPiece = whiteBoard[position[0]][position[1]];
			blackBoard[position[0]][position[1]] = blackBoard[location[0]][location[1]];
			whiteBoard[position[0]][position[1]] = '0';
			blackBoard[location[0]][location[1]] = '0';
			if (blackCheck() == true)
			{
				whiteBoard[position[0]][position[1]] = takenPiece;
				blackBoard[location[0]][location[1]] = blackBoard[position[0]][position[1]];
				blackBoard[position[0]][position[1]] = '0';
				
				if (ai)
				{
					//this->ai.input(whiteBoard, blackBoard);
					//return Board::AImove();
				}
				std::cout << std::endl << "Move out of check" << std::endl;
				return Board::blackMove();
			}
			Board::updatePrevious(position, location);
			return true;
		}

		else
		{
			if (ai)
			{
				//this->ai.input(whiteBoard, blackBoard);
				//return Board::AImove();
			}
			Board::moveReset();
			Board::draw();
			return Board::blackMove();
		}
	}
	return true;
}

void Board::updatePrevious(int position[], int location[])
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			previousMove[x][y] = false;
		}
	}
	previousMove[position[0]][position[1]] = true;
	previousMove[location[0]][location[1]] = true;
}

bool Board::blackMove()
{
	bool blackPieceFound = false;
	int click;
	int position[2];
	int location[2];
	bool legalMove = false;
	int responce = 0;

	while (blackPieceFound == false)
	{
		click = display.click();
		if (click == 99)
		{
			responce = gameMenu(false, false);
			if (responce == 1)
			{
				return false;
			}
			else
			{
				draw();
				return blackMove();
			}
		}

		position[0] = click % 10;
		position[1] = click / 10;
		if (blackBoard[position[0]][position[1]] != '0'
			&& blackBoard[position[0]][position[1]] != 's'
			&& blackBoard[position[0]][position[1]] != 'O')
		{
			blackPieceFound = true;
		}
	}

	Board::moveReset();
	Board::blackSwitch(position, false);
	Board::blackNoMoveInCheck(position);
	Board::draw();

	click = display.click();
	location[0] = click % 10;
	location[1] = click / 10;

	if (!Board::makeTheMove(location, position, false))
	{
		return false;
	}
	Board::moveReset();
	return true;
}

bool Board::AImove()
{
	int time = rand() % 2 + 1;
	clock.restart();
	do
	{
		elapsed1 = clock.getElapsedTime();
	} while (elapsed1 <= sf::seconds(time));

	int position[2];
	int location[2];

	ai.input(whiteBoard, blackBoard);
	int move = ai.move(); //minAI.finalMove(whiteBoard, blackBoard, 0); //= 

	std::cout << move << std::endl;

	position[0] = move / 1000;
	position[1] = (move - position[0] * 1000) / 100;
	location[0] = (move - position[0] * 1000 - position[1] * 100) / 10;
	location[1] = move % 10;

	Board::moveReset();
	Board::blackSwitch(location, false);
	Board::blackNoMoveInCheck(position);
	Board::makeTheMove(position, location, false, true);
	Board::moveReset();

	return true;
}

bool Board::BlakeAImove()
{
	int time = rand() % 2 + 1;
	clock.restart();
	do
	{
		elapsed1 = clock.getElapsedTime();
	} while (elapsed1 <= sf::seconds(time));

	int position[2];
	int location[2];

	//blakeAI.input(whiteBoard, blackBoard);
	int move = 0;// = blakeAI.move();

	std::cout << move << std::endl;

	position[0] = move / 1000;
	position[1] = (move - position[0] * 1000) / 100;
	location[0] = (move - position[0] * 1000 - position[1] * 100) / 10;
	location[1] = move % 10;

	Board::moveReset();
	Board::blackSwitch(location, false);
	Board::blackNoMoveInCheck(position);
	Board::makeTheMove(position, location, true, true);
	Board::moveReset();

	return true;
}

void Board::draw(bool ai)
{
	bool whitePawn = false;
	bool blackPawn = false;
	int location[2];
	display.clear();
	int piece = 0;
	for (int position = BOARDSIZE / 2; position < BOARDSIZE; position++)
	{
		if (whiteBoard[position][0] == 'p')
		{
			display.input('q', 0, 0, 1);
			display.input('r', 1, 0, 1);
			display.input('b', 0, 1, 1);
			display.input('n', 1, 1, 1);
			whitePawn = true;
			location[0] = position;
			location[1] = 0;
		}
		if (whiteBoard[9][position - 5] == 'p')
		{
			display.input('q', 0, 0, 1);
			display.input('r', 1, 0, 1);
			display.input('b', 0, 1, 1);
			display.input('n', 1, 1, 1);
			whitePawn = true;
			location[0] = 9;
			location[1] = position - 5;
		}
		if (blackBoard[position - 5][9] == 'p')
		{
			display.input('q', 0, 0, 0);
			display.input('r', 1, 0, 0);
			display.input('b', 0, 1, 0);
			display.input('n', 1, 1, 0);
			blackPawn = true;
			location[0] = position - 5;
			location[1] = 9;
		}
		if (blackBoard[0][position] == 'p')
		{
			display.input('q', 0, 0, 0);
			display.input('r', 1, 0, 0);
			display.input('b', 0, 1, 0);
			display.input('n', 1, 1, 0);
			blackPawn = true;
			location[0] = 0;
			location[1] = position;
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (previousMove[x][y])
			{
				display.input('M', x, y, 1);
			}
		}
	}

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 's' && whiteBoard[x][y] != 'O')
			{
				display.input(whiteBoard[x][y], x, y, true);
			}
			else if (blackBoard[x][y] != '0' && blackBoard[x][y] != 's' && blackBoard[x][y] != 'O')
			{
				display.input(blackBoard[x][y], x, y, false);
			}
			if (moves[x][y] == true)
			{
				display.input('A', x, y, true);
			}
		}
	}

	if (Board::someoneInCheck())
	{
		display.input('C', 8, 8, 1);
	}
	if (Board::whiteMate())
	{
		display.input('c', 9, 8, 1);
		display.input('B', 4, 4, 1);
		display.input('w', 5, 4, 1);
	}
	if (Board::blackMate())
	{
		display.input('c', 9, 8, 1);
		display.input('W', 4, 4, 1);
		display.input('w', 5, 4, 1);
	}

	if (!whitePawn && !blackPawn)
	{
		display.input('m', 9, 9, 1);
	}

	display.display();

	int position = 0;
	bool goodUser = false;
	if (whitePawn)
	{
		while (goodUser == false)
		{
			position = display.click();

			switch (position)
			{
			case 0:
				//q
				whiteBoard[location[0]][location[1]] = 'q';
				goodUser = true;
				break;
			case 1:
				//r
				whiteBoard[location[0]][location[1]] = 'r';
				goodUser = true;
				break;
			case 10:
				//b
				whiteBoard[location[0]][location[1]] = 'b';
				goodUser = true;
				break;
			case 11:
				//n
				whiteBoard[location[0]][location[1]] = 'n';
				goodUser = true;
				break;
			default:
				break;
			}
		}
		return Board::draw(ai);
	}


	else if (blackPawn)
	{
		if (ai)
		{
			blackBoard[location[0]][location[1]] = 'q';
			return Board::draw(ai);
		}
		while (goodUser == false)
		{
			position = display.click();

			switch (position)
			{
			case 0:
				//q
				blackBoard[location[0]][location[1]] = 'q';
				goodUser = true;
				break;
			case 1:
				//r
				blackBoard[location[0]][location[1]] = 'r';
				goodUser = true;
				break;
			case 10:
				//b
				blackBoard[location[0]][location[1]] = 'b';
				goodUser = true;
				break;
			case 11:
				//n
				blackBoard[location[0]][location[1]] = 'n';
				goodUser = true;
				break;
			default:
				break;
			}
		}
		return Board::draw(ai);
	}
	/*for (int position = 0; position < BOARDSIZE; position++)
	{
		if (whiteBoard[position][0] == 'p')
		{
			while (piece >= 0)
			{
				piece = display.click();
			}
			switch (piece)
			{
			case -1:
				whiteBoard[position][0] = 'q';
				break;
			case -2:
				whiteBoard[position][0] = 'r';
				break;
			case -3:
				whiteBoard[position][0] = 'b';
				break;
			case -4:
				whiteBoard[position][0] = 'n';
			default:
				break;
			}
		}
		if (blackBoard[position][7] == 'p')
		{
			while (piece >= 0)
			{
				piece = display.click();
			}
			switch (piece)
			{
			case -1:
				blackBoard[position][7] = 'q';
				break;
			case -2:
				blackBoard[position][7] = 'r';
				break;
			case -3:
				blackBoard[position][7] = 'b';
				break;
			case -4:
				blackBoard[position][7] = 'n';
			default:
				break;
			}
		}
	}*/
}

void Board::moveReset()
{
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			moves[x][y] = 0;
		}
	}
}

void Board::whiteSwitch(int position[], bool castle)
{
	int origonalX = position[0];
	int origonalY = position[1];

	bool enemy = false;
	bool check = false;

	castleQueenside = false;
	castleKingside = false;

	char homeRow[BOARDSIZE];

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

		if (castle)
		{
			for (int position = 0; position < BOARDSIZE; position++)
			{
				homeRow[position] = whiteBoard[position][7];
			}
			if (whiteBoard[4][7] == 'k' && whiteKing == true)
			{
				if (whiteBoard[7][7] == 'r' && whiteBoard[6][7] == '0'
					&& whiteBoard[5][7] == '0'
					&& blackBoard[7][7] == '0' && blackBoard[6][7] == '0'
					&& blackBoard[5][7] == '0'
					&& rightWhiteRook == true)
				{

					if (whiteCheck())
					{
						check = true;
					}
					for (int position = 5; position < BOARDSIZE; position++)
					{

						whiteBoard[position][7] = 'k';
						whiteBoard[position - 1][7] = '0';
						if (whiteCheck())
						{
							check = true;
						}

					}
					for (int position = 0; position < BOARDSIZE; position++)
					{
						whiteBoard[position][7] = homeRow[position];
					}
					if (check == false)
					{
						castleKingside = true;

					}

				}
				check = false;
				if (whiteBoard[0][7] == 'r' && whiteBoard[1][7] == '0'
					&& whiteBoard[2][7] == '0' && whiteBoard[3][7] == '0'
					&& blackBoard[0][7] == '0' && blackBoard[1][7] == '0'
					&& blackBoard[2][7] == '0' && blackBoard[3][7] == '0'
					&& leftWhiteRook == true)
				{
					if (whiteCheck())
					{
						check = true;
					}
					for (int position = 3; position >= 0; position--)
					{

						whiteBoard[position][7] = 'k';
						whiteBoard[position + 1][7] = '0';
						if (whiteCheck())
						{
							check = true;
						}

					}
					for (int position = 0; position < BOARDSIZE; position++)
					{
						whiteBoard[position][7] = homeRow[position];
					}
					if (check == false)
					{
						castleQueenside = true;
					}
				}

			}

			for (int x = 0; x < BOARDSIZE; x++)
			{
				for (int y = 0; y < BOARDSIZE; y++)
				{
					moves[x][y] = false;
				}
			}
		}

		if (castleKingside)
		{
			moves[6][7] = true;
		}
		if (castleQueenside)
		{
			moves[2][7] = true;
		}

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

void Board::blackSwitch(int position[], bool castle)
{
	int origonalX = position[0];
	int origonalY = position[1];

	bool enemy = false;
	bool check = false;

	castleQueenside = false;
	castleKingside = false;

	char homeRow[BOARDSIZE];

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

		if (castle)
		{
			for (int position = 0; position < BOARDSIZE; position++)
			{
				homeRow[position] = blackBoard[position][0];
			}
			if (blackBoard[4][0] == 'k' && blackKing == true)
			{
				if (whiteBoard[7][0] == '0' && whiteBoard[6][0] == '0'
					&& whiteBoard[5][0] == '0'
					&& blackBoard[7][0] == 'r' && blackBoard[6][0] == '0'
					&& blackBoard[5][0] == '0'
					&& rightBlackRook == true)
				{

					if (blackCheck())
					{
						check = true;
					}
					for (int position = 5; position < BOARDSIZE; position++)
					{

						blackBoard[position][0] = 'k';
						blackBoard[position - 1][0] = '0';
						if (blackCheck())
						{
							check = true;
						}

					}
					for (int position = 0; position < BOARDSIZE; position++)
					{
						blackBoard[position][0] = homeRow[position];
					}
					if (check == false)
					{
						castleKingside = true;

					}

				}
				check = false;
				if (whiteBoard[0][0] == '0' && whiteBoard[1][0] == '0'
					&& whiteBoard[2][0] == '0' && whiteBoard[3][0] == '0'
					&& blackBoard[0][0] == 'r' && blackBoard[1][0] == '0'
					&& blackBoard[2][0] == '0' && blackBoard[3][0] == '0'
					&& leftBlackRook == true)
				{
					if (blackCheck())
					{
						check = true;
					}
					for (int position = 3; position >= 0; position--)
					{

						blackBoard[position][0] = 'k';
						blackBoard[position + 1][0] = '0';
						if (blackCheck())
						{
							check = true;
						}

					}
					for (int position = 0; position < BOARDSIZE; position++)
					{
						blackBoard[position][0] = homeRow[position];
					}
					if (check == false)
					{
						castleQueenside = true;
					}
				}

			}

			for (int x = 0; x < BOARDSIZE; x++)
			{
				for (int y = 0; y < BOARDSIZE; y++)
				{
					moves[x][y] = false;
				}
			}
		}

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


