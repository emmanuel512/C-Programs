
/*********C++ Implementation of Pig Game**********/
//#include "stdafx.h"
#include <iostream>
#include <string>
#include "PigGame.h"	


int main()
{
	std::cout << "Welcome to Pig Game" << std::endl;

	string player;
	string computer = "AI";

	std::cout << "Enter your name: " << std::endl;
	cin >> player;

	Pig Game(player, computer, false);
	Game.play(); //Run the pig game
}
