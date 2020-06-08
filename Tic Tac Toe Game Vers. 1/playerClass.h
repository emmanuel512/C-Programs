#include <string>
#include <iostream>

using namespace std;


class Player
{
	private:
		string Name;

	public:
		string boardPiece;
		bool haveWon; // Bool to represent the player with the winning condition

		Player(string playerName)
		{
			setName(playerName);
		}

		void setName(string playerName)
		{
			Name = playerName;
		}

		string returnName()
		{
			return Name;
		}

		void makeMove(unsigned int &xPosition, unsigned int &yPosition)
		{
			std::cout << "Enter where you would like to place your board piece " << this->returnName() << std::endl;
			std::cout << "Enter row: ";
			std::cin >> xPosition;
			std::cout << "Enter col: ";
			std::cin >> yPosition;
			xPosition-=1; // Adjust it for the 0 index base
			yPosition-=1; // Adjust it for the 0 index base 
			std::cout << "Checking if placement is valid ....... " << std::endl; // Debugging purpose
		}

};
