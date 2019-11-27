#include <SFML\Graphics.hpp>
#include <iostream>
#include "board.h"
#include "display.h"
#include <Windows.h>

bool localGame(Board& board);
bool singlePlayer(Board& board);

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	Board board;

	try
	{
		//board.BlakevsAI();
		while (true)
		{
			int choice = board.menu();
			if (choice == -1)
			{
				return 0;
			}
		}
	}
	catch (int error)
	{
		//ShowWindow(GetConsoleWindow(), SW_RESTORE);
		return error;
	}
}

bool localGame(Board& board)
{
	board.draw();
	while (true)
	{
		sf::Clock clock;
		sf::Time elapsed1;
		board.draw();
		board.draw();
		if (board.whiteMate())
		{
			std::cout << "Black Wins!!!" << std::endl;
			return true;
		}
		if (board.whiteCheck())
		{
			std::cout << "White in Check" << std::endl;
		}

		board.whiteMove();

		board.draw();
		board.draw();
		if (board.blackMate())
		{
			std::cout << "White Wins!!!" << std::endl;
		}
		if (board.blackCheck())
		{
			std::cout << "Black in Check" << std::endl;
		}

		board.blackMove();
	}
}

bool singlePlayer(Board& board)
{
	board.draw(false);
	while (true)
	{
		sf::Clock clock;
		sf::Time elapsed1;
		board.draw(true);
		if (board.whiteMate())
		{
			std::cout << "Black Wins!!!" << std::endl;
			return true;
		}
		if (board.whiteCheck())
		{
			std::cout << "White in Check" << std::endl;
		}

		board.whiteMove();

		board.draw(true);
		if (board.blackMate())
		{
			std::cout << "White Wins!!!" << std::endl;
			return true;
		}
		if (board.blackCheck())
		{
			std::cout << "Black in Check" << std::endl;
		}

		board.AImove();
	}
}


/*
while (true)
{
int choice = board.menu();

if (choice == 1)
{
singlePlayer(board);
}
if (choice == 2)
{
localGame(board);
}
if (choice == -1)
{
return;
}

board.display.click();
board.reset();
}
*/