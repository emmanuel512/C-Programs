#include <string>
#include <iostream>
#include <cstdlib>
#include "playerClass.h"

#define ROWS 3
#define COLS 3

using namespace std;

class TicTacToe
{
	public:
		// This represents the square board in which x and o will be placed
		string squareBoard[ROWS][COLS];

		unsigned int xPosition; // Row position 
		unsigned int yPosition; // Col position

		bool whoseTurn; // Set this true  
		
		Player *player1;
		Player *player2;

		TicTacToe(Player *p1, Player *p2)
		{
			std::cout << "TicTacToe game created." << std::endl;
			player1 = p1;
			player2 = p2;
			whoseTurn = true;
			player1->boardPiece = "X ";
			player2->boardPiece = "O "; 
		}

		~TicTacToe()
		{
			std::cout << "Destroying game and player objects" << std::endl;
			free(player1);
			free(player2);
			exit(1);
		}

		// Print tic tac toe board function
		void printBoard()
		{
			std::cout << "----------------" << std::endl;
			for(int i = 0; i < ROWS; i++)
			{
				std::cout << "| ";
				for(int j = 0; j < COLS; j++)
				{
					std::cout << squareBoard[i][j];
					std::cout << " | ";
				}
				std::cout << std::endl;
				std::cout << "----------------" << std::endl;
			}
		}

		// Print players name function
		void introducePlayers()
		{
			std::cout << "Welcome player 1: " << player1->returnName() << std::endl;
			std::cout << "Welcome player 2: " << player2->returnName() << std::endl;
			std::cout << std::endl;
			std::cout << player1->returnName() << " your board piece is a " << player1->boardPiece << std::endl;
			std::cout << player2->returnName() << " your board piece is a " << player2->boardPiece << std::endl;
			std::cout << std::endl;
		}

		void printInstructions()
		{
			std::cout << "To play a board piece enter row and col position corresponding to where you would like the piece to be placed" << std::endl;
		}

		// Intialize board to placeholder string
		void initializeBoard()
		{
			for(int i = 0; i < ROWS; i++)
			{
				for(int j = 0; j < COLS; j++)
				{
					squareBoard[i][j] = "- ";
				}
			}
		}

		void endGame(Player *winner)
		{
			string decision;
			std::cout << winner->returnName() << " won !!!" << std::endl;
			std::cout << "Game Over" << std::endl;
			this->printBoard();
			std::cout << "Do you want to play again ? Type Yes or No" << std::endl;
			std::cin >> decision;
			if(decision == "Yes")
			{
				this->startGame();
			}
			else
			{
				this->~TicTacToe();
			}
	
		}

		void endGame()
		{
			string decision;
			std::cout << "Draw !!! " << std::endl;
			std::cout << "Game Over" << std::endl;
			this->printBoard();
			std::cout << "Do you want to play again ? Type Yes or No" << std::endl;
			std::cin >> decision;
			if(decision == "Yes")
			{
				this->startGame();
			}
			else
			{
				this->~TicTacToe();
			}
		}

		// Function that checks when a winning condition is met
		bool hasWon(string boardPiece)
		{
			// Three pieces straight across or diagonally 
			// All cases are being checked
			std::cout << "Checking if someone has won .... " << std::endl; // Debugging
			if(this->squareBoard[0][0] == boardPiece && this->squareBoard[0][1] == boardPiece && this->squareBoard[0][2] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[1][0] == boardPiece && this->squareBoard[1][1] == boardPiece && this->squareBoard[1][2] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[2][0] == boardPiece && this->squareBoard[2][1] == boardPiece && this->squareBoard[2][2] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[0][0] == boardPiece && this->squareBoard[1][1] == boardPiece && this->squareBoard[2][2] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[0][2] == boardPiece && this->squareBoard[1][1] == boardPiece && this->squareBoard[2][0] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[0][0] == boardPiece && this->squareBoard[1][0] == boardPiece && this->squareBoard[2][0] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[0][1] == boardPiece && this->squareBoard[1][1] == boardPiece && this->squareBoard[2][1] == boardPiece)
			{
				return true;
			}
			else if(this->squareBoard[0][2] == boardPiece && this->squareBoard[1][2] == boardPiece && this->squareBoard[2][2] == boardPiece)
			{
				return true;
			}
			std::cout << "No one has won yet .... " << std::endl; // Debugging
			std::cout << std::endl;
			return false;
		}

		// Function checks the board to see if draw condition is met
		bool isDraw()
		{
			for(int i = 0; i < ROWS; i++)
			{
				for(int j = 0; i < COLS; j++)
				{
					if(this->squareBoard[i][j] == "- ")
					{
						return true;
					}
				}
			}
			return false;
		}
		
		// Function that deterimines whether or not the move a player is making is allowed or not
		bool isValidMove(Player *playerTurn, unsigned int row, unsigned int col)
		{
	
			if(row < 3)
			{
				if(col < 3)
				{
					if(this->squareBoard[row][col] == "- ")
					{
						std::cout << "Tile placement is valid ..... " << std::endl;
						this->squareBoard[row][col] = playerTurn->boardPiece;
						this->printBoard();
						return true;
					}
				}
			}
			std::cout << "Tile placement is invalid..... " << std::endl;
			return false;
		}

		// Start game function
		void startGame()
		{
			this->initializeBoard();
			this->introducePlayers();
			this->printBoard();
			this->printInstructions();
			this->playerTurn(player1);
		}

		void playerTurn(Player *playerTurn)
		{
			bool playersDraw;
			bool playerWon;
			bool changeTurn; 
			do
			{
				playerTurn->makeMove(this->xPosition, this->yPosition); // Fills in position attribute from player object signifying where player wants to place their piece
				changeTurn = this->isValidMove(playerTurn,this->xPosition, this->yPosition); // This function will return whether move was valid that way turn changes to other player
			}while(changeTurn != true);

			// Check if winning condition has been met
			playerWon = this->hasWon(playerTurn->boardPiece);

			if(playerWon)
			{
				//std::cout << "Someone has won ... " << std::endl; // Debugging
				this->endGame(playerTurn);
			}

			playersDraw = isDraw();

			if(playersDraw != true)
			{
				this->endGame();
			}

			whoseTurn = !whoseTurn; // This reverse the whoseTurn bool value therefore changing to other player's turn

			if(whoseTurn)
			{
				this->playerTurn(this->player1);
			}

			else
			{
				this->playerTurn(this->player2);
			}
		}

};


