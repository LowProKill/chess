#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



class Display
{
public:
	Display();

	void textures(bool starWars);

	void input(char type, int X, int Y, bool white);

	void display();

	void clear();

	int click();

	int menuClick();

private:

	int windowSize = 800;

	bool closed = false;
	bool texturesThatLive[17];

	sf::Clock clock;
	sf::Time elapsed1;

	sf::Texture boardText;
	sf::Texture whiteText[6];
	sf::Texture blackText[6];

	sf::Texture preiviousMove;
	sf::Texture avaiableMove;
	sf::Texture check;
	sf::Texture mate;
	sf::Texture single;
	sf::Texture multi;
	sf::Texture player;
	sf::Texture menu;
	sf::Texture restart;
	sf::Texture whiteWins;
	sf::Texture blackWins;
	sf::Texture wins;
	sf::Texture Quit;
	sf::Texture save;
	sf::Texture load;

	sf::Sprite piece;
	sf::Sprite board;
	sf::RenderWindow Window;
};