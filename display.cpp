#include "display.h"
#include <Windows.h>

Display::Display()
{
	sf::Texture logo;
	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	windowSize = sf::VideoMode::getDesktopMode().height;
	sf::Sprite logoSprite;
	Window.create(desktop, "Diagonal Chess", sf::Style::Fullscreen);

	for (int x = 0; x < 17; x++)
	{
		texturesThatLive[x] = true;
	}

	if (!boardText.loadFromFile("textures/gameBoard.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[0] = false;
	}
	if (!preiviousMove.loadFromFile("textures/previousMove.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[1] = false;
	}
	if (!avaiableMove.loadFromFile("textures/availableMove.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[2] = false;
	}
	if (!check.loadFromFile("textures/check.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[3] = false;
	}
	if (!mate.loadFromFile("textures/mate.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[4] = false;
	}
	if (!single.loadFromFile("textures/single.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[5] = false;
	}
	if (!multi.loadFromFile("textures/multi.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[6] = false;
	}
	if (!player.loadFromFile("textures/player.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[7] = false;
	}
	if (!menu.loadFromFile("textures/menu.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[8] = false;
	}
	if (!restart.loadFromFile("textures/restart.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[9] = false;
	}
	if (!whiteWins.loadFromFile("textures/whiteWins.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[10] = false;
	}
	if (!blackWins.loadFromFile("textures/blackWins.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[11] = false;
	}
	if (!wins.loadFromFile("textures/wins.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[12] = false;
	}
	if (!Quit.loadFromFile("textures/quit.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[13] = false;
	}
	if (!save.loadFromFile("textures/save.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[14] = false;
	}
	if (!load.loadFromFile("textures/load.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[15] = false;
	}
	if (!logo.loadFromFile("textures/Straight Edge Studios2.png"))
	{
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
		std::cout << "could not find texture";
		texturesThatLive[16] = false;
	}


	board.setTexture(boardText);
	board.setPosition(0, 0);
	board.setScale(windowSize/1000.0, windowSize/1000.0);

	logoSprite.setTexture(logo);
	Window.clear();
	Window.draw(logoSprite);
	Window.display();

	do
	{
		elapsed1 = clock.getElapsedTime();
	} while (elapsed1 <= sf::seconds(3));

	Window.clear();
	Window.draw(board);
	Window.display();
}

void Display::textures(bool starWars)
{
	if (!starWars)
	{

		whiteText[0].loadFromFile("textures/Wpawn.png");
		whiteText[1].loadFromFile("textures/Wrook.png");
		whiteText[2].loadFromFile("textures/Wknight.png");
		whiteText[3].loadFromFile("textures/Wbishop.png");
		whiteText[4].loadFromFile("textures/Wqueen.png");
		whiteText[5].loadFromFile("textures/Wking.png");

		blackText[0].loadFromFile("textures/Bpawn.png");
		blackText[1].loadFromFile("textures/Brook.png");
		blackText[2].loadFromFile("textures/Bknight.png");
		blackText[3].loadFromFile("textures/Bbishop.png");
		blackText[4].loadFromFile("textures/Bqueen.png");
		blackText[5].loadFromFile("textures/Bking.png");
	}

	else if (starWars)
	{
		whiteText[0].loadFromFile("textures/starwars/Wpawn.png");
		whiteText[1].loadFromFile("textures/starwars/Wrook.png");
		whiteText[2].loadFromFile("textures/starwars/Wknight.png");
		whiteText[3].loadFromFile("textures/starwars/Wbishop.png");
		whiteText[4].loadFromFile("textures/starwars/Wqueen.png");
		whiteText[5].loadFromFile("textures/starwars/Wking.png");

		blackText[0].loadFromFile("textures/starwars/Bpawn.png");
		blackText[1].loadFromFile("textures/starwars/Brook.png");
		blackText[2].loadFromFile("textures/starwars/Bknight.png");
		blackText[3].loadFromFile("textures/starwars/Bbishop.png");
		blackText[4].loadFromFile("textures/starwars/Bqueen.png");
		blackText[5].loadFromFile("textures/starwars/Bking.png");
	}
}

void Display::input(char type, int X, int Y, bool white)
{
	X = (windowSize / 10.0) * X;
	Y = (windowSize / 10.0) * Y;

	switch (type)
	{
	case 'M':
		if (!texturesThatLive[1])
		piece.setTexture(preiviousMove);
		break;
	case 'm':
		if (!texturesThatLive[8])
		piece.setTexture(menu);
		break;
	case 'A':
		if (!texturesThatLive[2])
		piece.setTexture(avaiableMove);
		break;
	case 'C':
		if (!texturesThatLive[3])
		piece.setTexture(check);
		break;
	case 'c':
		if (!texturesThatLive[4])
		piece.setTexture(mate);
		break;
	case 'S':
		if (!texturesThatLive[5])
		piece.setTexture(single);
		break;
	case 'L':
		if (!texturesThatLive[6])
		piece.setTexture(multi);

		break;
	case 'E':
		if (!texturesThatLive[7])
		piece.setTexture(player);
		break;
	case 'Q':
		if (!texturesThatLive[13])
		piece.setTexture(Quit);
		break;
	case 'R':
		if (!texturesThatLive[9])
		piece.setTexture(restart);
		break;
	case 'W':
		if (!texturesThatLive[10])
		piece.setTexture(whiteWins);
		break;
	case 'B':
		if (!texturesThatLive[11])
		piece.setTexture(blackWins);
		break;
	case 'w':
		if (!texturesThatLive[12])
		piece.setTexture(wins);
		break;
	case 'G':
		if (!texturesThatLive[14])
		piece.setTexture(save);
		break;
	case'g':
		if (!texturesThatLive[15])
		piece.setTexture(load);
	default:
		break;

	}

	if (white == true)
	{
		switch (type)
		{
		case 'p':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[0]);
			break;
		case 'r':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[1]);
			break;
		case 'n':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[2]);
			break;
		case 'b':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[3]);
			break;
		case 'q':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[4]);
			break;
		case 'k':
			//if (!texturesThatLive[1])
			piece.setTexture(whiteText[5]);
			break;
		default:
			break;
		}
	}

	else
	{
		switch (type)
		{
		case 'p':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[0]);
			break;
		case 'r':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[1]);
			break;
		case 'n':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[2]);
			break;
		case 'b':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[3]);
			break;
		case 'q':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[4]);
			break;
		case 'k':
			//if (!texturesThatLive[1])
			piece.setTexture(blackText[5]);
			break;
		default:
			break;
		}
	}

	piece.setPosition(X, Y);

	piece.setScale((windowSize / 10.0 / 256.0), (windowSize / 10.0 / 256.0));

	Window.draw(piece);
}

void Display::display()
{
	Window.display();
}

void Display::clear()
{
	Window.clear();
	Window.draw(board);
}

int Display::click()
{
	sf::Event event;
	clock.restart();
	do
	{
		elapsed1 = clock.getElapsedTime();
	} while (elapsed1 <= sf::seconds(0.1));
	bool button = false;
	int mouseX = 0;
	int mouseY = 0;
	while (button == false)
	{
		mouseX = sf::Mouse::getPosition(Window).x;
		mouseY = sf::Mouse::getPosition(Window).y;
		button = sf::Mouse::isButtonPressed(sf::Mouse::Left);


		Window.pollEvent(event);
		if (event.type == sf::Event::Closed)
		{
			throw 1;
			closed = true;
		}

		clock.restart();
		do
		{
			elapsed1 = clock.getElapsedTime();
		} while (elapsed1 <= sf::seconds(0.05));
	}

	mouseX = (mouseX * 10.0 / windowSize);
	mouseY = (mouseY * 10.0 / windowSize);
	
	std::cout << mouseX << " " << mouseY << std::endl;
	int value = mouseY * 10 + mouseX;
	std::cout << value << std::endl;
	return value;
}

int Display::menuClick()
{
	sf::Event event;
	clock.restart();
	do
	{
		elapsed1 = clock.getElapsedTime();
	} while (elapsed1 <= sf::seconds(0.1));
	bool button = false;
	int mouseX = 0;
	int mouseY = 0;
	while (button == false)
	{
		mouseX = sf::Mouse::getPosition(Window).x;
		mouseY = sf::Mouse::getPosition(Window).y;
		button = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		Window.pollEvent(event);
		if (event.type == sf::Event::Closed)
		{
			throw 1;
			closed = true;
		}

		clock.restart();
		do
		{
			elapsed1 = clock.getElapsedTime();
		} while (elapsed1 <= sf::seconds(0.05));
	}

	mouseX = (mouseX * 10.0 / windowSize);
	mouseY = (mouseY * 10.0 / windowSize);

	std::cout << mouseX << " " << mouseY << std::endl;
	int value = mouseY * 10 + mouseX;
	std::cout << value << std::endl;
	return value;

}