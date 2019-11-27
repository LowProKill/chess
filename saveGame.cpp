#include "saveGame.h"

bool saveGame::save(char whiteBoard[10][10], char blackBoard[10][10], bool whoseTurn, bool ai)
{
	fileThing.open("data/save.dat", std::ofstream::out | std::ofstream::trunc);

	if (!fileThing.is_open())
	{
		return false;
	}
	string whiteLine = "";
	string blackLine = "";

	fileThing << "Do not modify data, if corrupted save over or delete \n";

	for (int x = 0; x < 10; x++)
	{
		whiteLine = "";
		blackLine = "";
		for (int y = 0; y < 10; y++)
		{
			switch (whiteBoard[x][y])
			{
				// p = 70
				// n = 6E
				// b = 62
				// r = 72
				// q = 71
				// K = 4B
				// O = 4F
				// 0 = 30
			case 'p':
				whiteLine += "70";
				break;

			case 'n':
				whiteLine += "6E";
				break;

			case 'b':
				whiteLine += "62";
				break;

			case 'r':
				whiteLine += "72";
				break;

			case 'q':
				whiteLine += "71";
				break;

			case 'k':
				whiteLine += "4B";
				break;

			case 'O':
				whiteLine += "4F";
				break;

			case '0':
				whiteLine += "30";
				break;

			default:
				break;
			}
			switch (blackBoard[x][y])
			{
				// p = 70
				// n = 6E
				// b = 62
				// r = 72
				// q = 71
				// K = 4B
				// O = 4F
				// 0 = 30
			case 'p':
				blackLine += "70";
				break;

			case 'n':
				blackLine += "6E";
				break;

			case 'b':
				blackLine += "62";
				break;

			case 'r':
				blackLine += "72";
				break;

			case 'q':
				blackLine += "71";
				break;

			case 'k':
				blackLine += "4B";
				break;

			case 'O':
				blackLine += "4F";
				break;

			case '0':
				blackLine += "30";
				break;

			default:
				break;
			}
		}
		fileThing << whiteLine << "  " << blackLine << endl;
	}
	fileThing << whoseTurn << ai << endl;
	fileThing.close();
	return true;
}

int saveGame::load(char whiteBoard[10][10], char blackBoard[10][10])
{
	ifstream thing;
	thing.open("data/save.dat");
	string line;
	string chr;
	char c;
	if (!thing.is_open())
	{
		return 0;
	}

	//"Do not modify data, if corrupted save over or delete \n"
	for (int x = 0; x < 54; x++)
	{
		thing.get(c);
		line += c;
	}
	if (line != "Do not modify data, if corrupted save over or delete \n")
	{
		return -1;
	}

	char wBoard[10][10];
	char bBoard[10][10];
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			wBoard[x][y] = whiteBoard[x][y];
			bBoard[x][y] = blackBoard[x][y];
		}
	}

	for (int x = 0; x < 10; x++)
	{
		// p = 70
		// n = 6E
		// b = 62
		// r = 72
		// q = 71
		// K = 4B
		// O = 4F
		// 0 = 30
		line = "";
		for (int y = 0; y < 21; y++)
		{
			chr = "";
			thing.get(c);
			switch (c)
			{
			case '7':
			case '0':
			case '6':
			case 'E':
			case '2':
			case '1':
			case '4':
			case 'B':
			case 'F':
			case '3':
			case ' ':
			case '\n':
				break;
			default:
				return -1;
				break;
			}
			if (thing.eof())
			{
				return -1;
			}
			else if (c == '\n')
			{
				thing.get(c);
				switch (c)
				{
				case '7':
				case '0':
				case '6':
				case 'E':
				case '2':
				case '1':
				case '4':
				case 'B':
				case 'F':
				case '3':
				case '\n':
				case ' ':
					break;
				default:
					return -1;
					break;
				}
				if (thing.eof())
				{
					return -1;
				}
			}
			chr += c;
			thing.get(c);
			if (thing.eof())
			{
				return -1;
			}
			switch (c)
			{
			case '7':
			case '0':
			case '6':
			case 'E':
			case '2':
			case '1':
			case '4':
			case 'B':
			case 'F':
			case '3':
			case ' ':
			case '\n':
				break;
			default:
				return -1;
				break;
			}
			chr += c;

			if (chr == "70")
			{
				line += "p";
			}
			else if (chr == "6E")
			{
				line += "n";
			}
			else if (chr == "62")
			{
				line += "b";
			}
			else if (chr == "72")
			{
				line += "r";
			}
			else if (chr == "71")
			{
				line += "q";
			}
			else if (chr == "4B")
			{
				line += "k";
			}
			else if (chr == "4F")
			{
				line += "O";
			}
			else if (chr == "30")
			{
				line += "0";
			}
			else if (chr == "  ")
			{
				line += "  ";
			}
			else
			{
				return -1;
			}
		}
		for (int y = 0; y < 10; y++)
		{

			whiteBoard[x][y] = line[y];
			blackBoard[x][y] = line[y + 12];
		}
	}

	line = "";
	thing.get(c);
	if (thing.eof())
	{
		return -1;
	}
	switch (c)
	{
	case '1':
	case '0':
	case '\n':
		break;
	default:
		return -1;
		break;
	}
	line += c;
	thing.get(c);
	if (thing.eof())
	{
		return -1;
	}
	switch (c)
	{
	case '1':
	case '0':
	case '\n':
		break;
	default:
		return -1;
		break;
	}
	line += c;

	if (line[1] == '1')
	{
		return 11;
	}
	else if (line[0] == '1')
	{
		return 21;
	}
	else if (line[0] == '0')
	{
		return 22;
	}

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			whiteBoard[x][y] = wBoard[x][y];
			blackBoard[x][y] = bBoard[x][y];
		}
	}
	thing.close();

	return -1;
}