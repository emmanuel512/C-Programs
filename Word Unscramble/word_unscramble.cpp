// Word Jumble Game 
// Written in C/C++

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>

#define MAX_GUESS_WORDS 10
#define MAX_WORD_LENGTH 15

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function declarations
char *reverse_word(char *word);
char *scramble_word(char *word);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char *reverse_word(char *word)
{
	char *new_word = (char *)malloc(sizeof(word)); // Create new word buffer size of word
	short string_length = strlen(word);	

	for(int i = 0; i < string_length; i++)
	{
		new_word[string_length-1-i] = word[i];		
	}
	return new_word;
}

char *scramble_word(char *word)
{
	char *new_word = (char *)malloc(sizeof(word)); // Create new word buffer size of word
	short string_length = strlen(word);	
	char temp;
	// How do I scramble this word? maybe reverse it first?
	// Try shifting first letter to back 
	for(int i = 0; i < string_length; i++)
	{
		if(i == 0)
		{
			temp = word[i];
			continue;
		}
		if(i == string_length-1)
		{
			new_word[i] = temp;
		}
		new_word[i-1] = word[i];
	}
	new_word = reverse_word(new_word);	
	return new_word;
}


int main()
{
	std::cout << "Welcome to Word Jumble\n";
	char *unscrambled_words[MAX_GUESS_WORDS] = {"road", "light", "heart", "right", "professional", "basketball", "hockey", "america", "laptop", "encyclopedia"};
	
	std::cout << "Given a jumbled word, guess the unjumbled world\n";

	// Loop through each word in list of unscrambled words
	for(int i = 0; i < MAX_GUESS_WORDS; i++)
	{
		std::cout << "Word number: " << i+1 << "\n";
		char guess[MAX_WORD_LENGTH];
		char *scrambled_word = scramble_word(unscrambled_words[i]);
		while(1)
		{
			std::cout << "Scrambled word is " << scrambled_word << "\n";
			std::cout << "Guess a word\n";
			memset(guess, 0, sizeof(guess));
			fgets(guess, MAX_WORD_LENGTH, stdin);
			std::cout << "Guessed word is " << guess << "\n";

			if(strcmp(guess, unscrambled_words[i]) == 10 && i != MAX_GUESS_WORDS-1)
			{
				std::cout << "Right word guessed, onto the next word\n";
				break;
			}
			else if(strcmp(guess, unscrambled_words[i]) == 10)
			{
				std::cout << "Right word guessed, end of game\n";
				break;
			}
			else
			{
				std::cout << "Incorrect guess word\n";
			}
		}
	}
	return 0; // Indication that program was successful
}