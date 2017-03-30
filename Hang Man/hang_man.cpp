// Hang man game (Holidays)
// Written in C++

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Create a list of words for the game

std::vector<string> words;

void initialize_list(vector<string> &list)
{
	list.push_back("Christmas");
	list.push_back("Thanksgiving");
	list.push_back("Easter");
	list.push_back("New Years");
	list.push_back("Valentines");
	list.push_back("Independence");
	list.push_back("Halloween");
}

void find_and_replace_all(string &a, string &b, char &c)
{
	for(int i = 0; i < a.size(); i++)
	{
		if(a[i] == c)
		{
			b[i] = c;
		}
	}
}

void userplay(string &word)
{
	string hidden_word, guess;
	int num_of_guess, guess_left;
	vector<string> guesses;
	
	// Hide all letters of word
	hidden_word.append(word.size(), '-');
	num_of_guess = 0;

	// Game loop while guess isn't word and not quit
	while(guess != "quit" && num_of_guess < 15)
	{
		if(hidden_word == word)
		{
			std::cout << hidden_word << "\n";
			std::cout << "The hidden word has been completely revealed! You win.\nGame Over\n";
			return;
		}

		std::cout << "Hidden word: " << hidden_word << "\n";
		std::cout << "Enter a letter or word, or quit to end the game\n";
		cin >> guess;
		num_of_guess++;
		guess_left = 15 - num_of_guess;

		if(guess == word)
		{
			std::cout << "You have guessed the correct word!\n";
			std::cout << "The word was " << word << "\n";
			std::cout << "Game over\n";
			return;
		}

		// Check if letter is within the random word
		if(guess.size() == 1 && word.find(guess) != string::npos)
		{
			std::cout << "You entered a single letter\n";
			char letter = word[word.find(guess)];	
			find_and_replace_all(word, hidden_word, letter);
			std::cout << "You have " << guess_left << " guesses left\n";
			continue;
		}

		if(guess == "quit")
		{
			std::cout << "You quit, game over!!!\n";
			exit(1);
		}

		else
		{
			std::cout << "You incorrect word or letter\nGuess again?\n";
			std::cout << "You have " << guess_left << " guesses left\n";
		}
	}

	std::cout << "You ran out of guess! Better luck next time :D\n";
	return;
}

int generate_rand_num(int range)
{
	srand((int) time(NULL));
	return (rand() % range) + 1;
}

int main(void)
{
	std::cout << "Welcome to hangman!\n";

	initialize_list(words);

	int rand_num;
	// Pick a word random word
	rand_num = generate_rand_num(words.size() - 1);
	//std::cout << "Random word chosen is " << words[rand_num] << "\n"; // Debugging purpose
	userplay(words[rand_num]);

	return 0;
}