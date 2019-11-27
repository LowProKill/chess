#pragma once


//error in whiteSwitch white can move passed black pieces


struct bMoves
{
public:
	int move = -1;
	int score = 0;
};

struct myMove
{
private:
	const int BOARDSIZE = 10;
	int depth = 0;

	char whiteBoard[10][10];
	char blackBoard[10][10];
	bool moves[10][10];

	int pawnStat = 10;
	int knightStat = 30;
	int bishopStat = 30;
	int rookStat = 50;
	int queenStat = 90;
	int kingStat = 900;

public:
	int move = -1;

	int score = -9999;

	void updateBoard(char wBoard[10][10], char bBoard[10][10])
	{
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				whiteBoard[x][y] = wBoard[x][y];
				blackBoard[x][y] = bBoard[x][y];
			}
		}

	}

	void countEmUp()
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
						white += pawnStat;
						break;

					case 'n':
						white += knightStat;
						break;

					case 'b':
						white += bishopStat;
						break;

					case 'r':
						white += rookStat;
						break;

					case 'q':
						white += queenStat;
						break;

					case 'k':
						white += kingStat;
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
						black += pawnStat;
						break;

					case 'n':
						black += knightStat;
						break;

					case 'b':
						black += bishopStat;
						break;

					case 'r':
						black += rookStat;
						break;

					case 'q':
						black += queenStat;
						break;

					case 'k':
						black += kingStat;
						break;

					default:
						break;
					}
				}
			}
		}
		score = black - white;
		int position[2];
		int location[2];
		char piecesThatCanTakeIt[16] =
		{
			'0', '0', '0', '0',
			'0', '0', '0', '0',
			'0', '0', '0', '0',
			'0', '0', '0', '0'
		};
		int valueOfPiece = 0;
		position[0] = move / 1000;
		position[1] = (move - position[0] * 1000) / 100;
		location[0] = (move - position[0] * 1000 - position[1] * 100) / 10;
		location[1] = move % 10;
		char piece = blackBoard[position[0]][position[1]];
		if (whiteCheck())
		{
			score += 9;
		}
		//make trades
		if (canItBeGot(position, piecesThatCanTakeIt))
		{
			switch (piece)
			{
			case 'p':
				score -= pawnStat - 1;
				break;

			case 'n':
				score -= knightStat;
				break;

			case 'b':
				score -= bishopStat - 1;
				break;

			case 'r':
				score -= rookStat + 1;
				break;

			case 'q':
				score -= queenStat - 1;
				break;

			case 'k':
				break;

			default:
				break;
			}
		}
		// protect pieces and allow trades
		else if (canItBeGot(location, piecesThatCanTakeIt))
		{
			int where = 0;
			while (piecesThatCanTakeIt[where] != '0')
			{
				where++;
			}
			if (where > 1)
			{
				switch (piece)
				{
				case 'p':
					score += pawnStat;
					break;

				case 'n':
					score += knightStat;
					break;

				case 'b':
					score += bishopStat;
					break;

				case 'r':
					score += rookStat;
					break;

				case 'q':
					score += queenStat;
					break;

				default:
					break;
				}
			}
			else
			{
				switch (piecesThatCanTakeIt[0])
				{
				case 'p':
					valueOfPiece = pawnStat;
					break;

				case 'n':
					valueOfPiece = knightStat;
					break;

				case 'b':
					valueOfPiece = bishopStat;
					break;

				case 'r':
					valueOfPiece = rookStat;
					break;

				case 'q':
					valueOfPiece = queenStat;
					break;

				case 'k':
					if (isItDefended(position))
					{
						score += 20;
						valueOfPiece = kingStat;
					};
					break;

				default:
					break;
				}
				switch (piece)
				{
				case 'p':
					score += pawnStat - valueOfPiece;
					break;

				case 'n':
					score += knightStat - valueOfPiece;
					break;

				case 'b':
					score += bishopStat - valueOfPiece;
					break;

				case 'r':
					score += rookStat - valueOfPiece;
					break;

				case 'q':
					score += queenStat - valueOfPiece;
					break;

				case 'k':
					//score += kingStat - valueOfPiece;
					break;

				default:
					break;
				}
			}
		}
		if (whiteMate())
		{
			score += 99999;
		}
		if (piece == 'k')
		{
			score = score - 500;
		}
	}

	bool canItBeGot(int position[], char piecesThatCanDoIt[])
	{
		int location[2];
		int where = 0;
		bool gotten = false;
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moveReset();
				if (whiteBoard[x][y] != '0' && whiteBoard[x][y] != 'O')
				{
					location[0] = x;
					location[1] = y;
					whiteSwitch(location, 0);
					if (moves[position[0]][position[1]])
					{
						piecesThatCanDoIt[where] = whiteBoard[x][y];
						gotten = true;
					}
				}
			}
		}
		return gotten;
	}

	bool isItDefended(int position[])
	{
		int location[2];
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moveReset();
				if (blackBoard[x][y] != '0' && blackBoard[x][y] != 'O')
				{
					location[0] = x;
					location[1] = y;
					blackSwitch(location);
					if (moves[position[0]][position[1]])
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool whiteMate()
	{
		int position[2];
		char piece;
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
							whiteSwitch(position, 0);
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
		return true;
	}

	bool whiteCheck()
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
					blackSwitch(position);
				}
			}
		}

		if (moves[KingX][KingY] == true)
		{
			return true;
		}
		return false;
	}

	void blackSwitch(int position[])
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

	void whiteSwitch(int position[], bool castle)
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

	void moveReset()
	{
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
			{
				moves[x][y] = 0;
			}
		}
	}
};