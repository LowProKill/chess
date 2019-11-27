#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class saveGame
{
public:
	saveGame()
	{

	};

	bool save(char whiteBoard[10][10], char blackBoard[10][10], bool whoseTurn, bool ai);

	// return value key 0 = failed 11 = whites turn single player
	// 21 = whites turn two player 22 = blacks turn two player
	int load(char whiteBoard[10][10], char blackBoard[10][10]);

private:
	
	fstream fileThing;
	
};