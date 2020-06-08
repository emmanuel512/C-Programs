// Tic Tac Toe Game
// C++ Programming

#include <iostream>
#include <string>
#include "gameClass.h"
//#include "playerClass.h" I don't need to include this file again since it was included in gameClass.h

using namespace std;

int main()
{
	// Get Player names
	string player1;
	string player2;

	std::cout << "Enter player 1's name: ";
	std::cin >> player1;

	std::cout << "Enter player 2's name: ";
	std::cin >> player2;

	// Create Players
	Player p1 = Player(player1);
	Player p2 = Player(player2);	

	// Create TicToeGame object
	TicTacToe game = TicTacToe(&p1, &p2);

	game.startGame();

	return 0;
}