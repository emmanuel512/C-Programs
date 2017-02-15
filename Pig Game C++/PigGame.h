/***************Pig Game Class*************/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>

#define PLAYERS 2

using namespace std;

class Pig
{

private:
	//Variable Members
	vector<string> players;
	int scores[PLAYERS];
	bool whoseTurn;

public:
	//Constructor
	Pig(string a, string b, bool startTurn)
	{
		std::cout << "_______________ Pig Game has been created ______________" << std::endl;
		players.push_back(a); //Add Human 
		players.push_back(b); //Add AI 
		std::setw(10);
		std::cout << "Welcome players " << this->players[0] << " and " << this->players[1] << std::endl;
	}

	//Methods
	void userPlay()
	{
		std::cout << "\n";
		this->printScore();
		string decision;
		static int round = 1;
		int roundScore = 0;
		int diceRoll = 0;
		int lastRoll = 0;	
		
		std::cout << "Round: " << round << std::endl;
		decision = "yes";
			
	
		while (decision == "yes")
		{
			this->printScore();
			std::cout << "Round: " << round << " roll" << std::endl;
			diceRoll = this->generateRandNumber();

			//std::cout << diceRoll << std::endl;

			if (this->scores[0] >= 100)
			{
				this->won();
				//return;
			}

			if (diceRoll == 2)
			{
				std::cout << this->players[0] << " rolled a " << diceRoll << std::endl;
				std::cout << "You have lost your points for this round" << std::endl;
				roundScore = 0;
				this->whoseTurn = true;
				round += 1;
				this->computerPlay();
				//return;
			}

			if (lastRoll == 1)
			{
				if (diceRoll = 1)
				{
					std::cout << "You rolled 1 twice. All points gone" << std::endl;
					diceRoll = 0;
					this->scores[0] = 0;
					this->whoseTurn = true;
					round += 1;
					this->computerPlay();
				}
				if (diceRoll == 6)
				{
					std::cout << "Total points double" << std::endl;
					this->scores[0] = this->scores[0] * 2;
					//round += 1;
					lastRoll = diceRoll;
				}
			}
			else
			{
				roundScore += diceRoll;
				lastRoll = diceRoll;
				this->scores[0] += roundScore;
				//round += 1;
			}
			std::cout << this->players[0] << " rolled a " << diceRoll << std::endl;
			std::cout << "Total score is " << this->scores[0] << std::endl;
			std::cout << "Round score is " << roundScore << std::endl;
			std::cout << "Round: " << round << std::endl;
			std::cout << "If " << this->players[0] << " stops, total score is " << this->scores[0] << std::endl;
			std::cout << "Do you want to roll again ?" << std::endl;
			std::cout << "__________________________________" << std::endl;
			std::cin >> decision;
		}
		if (decision == "no")
		{
			round += 1;
			if(this->scores[0] < 100)
			{
				this->whoseTurn = true;
				this->computerPlay();	
			}
			else
			{
				this->won();
			}
			//return;
		}
	}

	void computerPlay()
	{
		std::cout << "\n";
		std::cout << "It is " << players[1] << "'s turn" << std::endl;
		this->printScore();
		static int round = 1;
		int roundScore = 0;
		int diceRoll = 0;
		int lastRoll = 0;
		int TimeUp;
		std::cout << "Round: " << round << std::endl;
		TimeUp = 0;
		while (TimeUp < 14)
		{
			this->printScore();
			std::cout << "Round " << round << " roll" << std::endl;
			diceRoll = this->generateRandNumber();

			//std::cout << diceRoll << std::endl;

			if (this->scores[1] >= 100)
			{
				this->won();
				//return;
			}

			if (diceRoll == 2)
			{
				std::cout << players[1] << " rolled a " << diceRoll << std::endl;
				std::cout << "You have lost your points for this round" << std::endl;
				roundScore = 0;
				whoseTurn = false;
				round += 1;
				this->userPlay();
				//return;
			}

			if (lastRoll == 1)
			{
				if (diceRoll == 1)
				{
					std::cout << "You rolled 1 twice. All points gone" << std::endl;
					diceRoll = 0;
					this->scores[1] = 0;
					whoseTurn = false;
					round += 1;
					this->userPlay();
					//return;
				}
				if (diceRoll == 6)
				{
					std::cout << "Total points double" << std::endl;
					this->scores[1] = scores[1] * 2;
					lastRoll = diceRoll;
					//round += 1;
				}
			}

			else
			{
				roundScore += diceRoll;
				lastRoll = diceRoll;
				this->scores[1] += roundScore;
				//round += 1;
			}
			std::cout << players[1] << " rolled a " << diceRoll << std::endl;
			std::cout << "Total score is " << this->scores[1] << std::endl;
			std::cout << "Current round score is " << roundScore << std::endl;
			std::cout << "Round: " << round << std::endl;
			std::cout << "If " << players[1] << " stops, total score is " << scores[1] << std::endl;
			std::cout << "__________________________________" << std::endl;
			//std::cout << "Do you want to roll again ?" << std::endl;
			//std::cin >> decision;

			TimeUp += this->generateRandNumber();
		}

		if (TimeUp >= 14)
		{
			this->printScore();
			std::cout << "AI has stopped" << std::endl;
			round += 1;
			if(this->scores[1] < 100)
			{
				this->whoseTurn = false;
				this->userPlay();
			}
			else
			{
				this->won();
			}
			//return;
		}
		
	}

	void won()
	{
		if (!this->whoseTurn)
		{
			std::cout << "The winner is " << players[0] << " with score of " << scores[0] << std::endl;
			this->printScore();
			this->endGame();
		}
		else
		{
			std::cout << "The winner is " << players[1] << " with score of " << scores[1] << std::endl;
			this->printScore();
			this->endGame();
		}
	}

	void printScore()
	{
		//Print array of scores
		std::cout << "__________________________________" << std::endl;
		for (int i = 0; i < PLAYERS; i++)
		{
			std::cout << this->players[i] << ": " << this->scores[i] << std::endl;
		}
		std::cout << "__________________________________" << std::endl;
		std::cout << "\n";
	}

	void play()
	{
		if (!this->whoseTurn)
		{
			return this->userPlay();
			//return;
		}
	}

	void endGame()
	{
		std::cout << "Game Over" << std::endl;
		exit(1);
	}

	int generateRandNumber()
	{
		srand((int) time(NULL));
		return (rand() % 6) + 1;
	}

};
