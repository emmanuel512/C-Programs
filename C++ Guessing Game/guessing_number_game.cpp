/********Number Guessing Game********/
/* Emmanuel Banjo
/* C++ Program
/************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include <string>

using namespace std;

int generateRandNumber(int range)
{
	srand((int) time(NULL));
	return (rand() % range) + 1;
}

void play()
{
	int range;

	std::cout << "Starting Guessing Game" << std::endl;

	std::cout << "How large should the guess range be? " << std::endl;

	cin >> range;	

	std::cout << "Guess range is between 1 and " << range << std::endl;

	int guessNumber = generateRandNumber(range);

	int numOfTries = 0;

	bool correctGuess;

	vector<int> guesses; //All the guess you have made
	
	do
	{
		std::cout << "Guess a number" << std::endl;

		correctGuess = false;

		int guess;

		cin >> guess;

		guesses.push_back(guess);

		if(guess == guessNumber)
		{
			numOfTries++;
			std::cout << "You have guessed the number correctly!" << std::endl;
			std::cout << "It took you " << numOfTries << " tries" << std::endl;
			correctGuess = true;
		}

		else if(guess > guessNumber)
		{
			std::cout << "You guessed too high" << std::endl;
			std::cout << "Try again !" << std::endl;
			numOfTries++;
			std::cout << "Guessed numbers: " << std::endl;
			for(int i = 0; i < guesses.size(); i++)
			{
				std::cout << guesses[i] << " | ";
			}
			std::cout << "\n";
		}

		else
		{
			std::cout << "You guessed too low" << std::endl;
			std::cout << "Try again !" << std::endl;
			numOfTries++;
			std::cout << "Guessed numbers: " << std::endl;
			for(int i = 0; i < guesses.size(); i++)
			{
				std::cout << guesses[i] << " | ";
			}
			std::cout << "\n";
		}	
	}while(correctGuess == false);

	std::cout << "End of game" << std::endl;
}

int main()
{	

	play();
}