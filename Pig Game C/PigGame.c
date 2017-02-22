/**********************************/
//Emmanuel Banjo
//C Implementation of Pig Game
//PigGame.c
/**********************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "PigGame.h"

int generateRandNumber()
{
	time_t t;
	srand((unsigned) time(&t));
	return (rand() % 6) + 1;
}


void computerPlay()
{
	printScores();
	static int round = 1;
	int roundScore = 0;
	int lastRoll = 0;
	int diceRoll;
	int timeUp = 0;
	
	printf("Round: %d\n", round);
	do
	{
		//printScores();
		diceRoll = generateRandNumber();
		if(scores[PLAYER2] >= 100)
		{
			won();
		}

		else if(diceRoll == 2)
		{
			printf("%c rolled a %d\n", names[PLAYER1], diceRoll);
			printf("All points lost this round\n");
			roundScore = 0;
			whoseTurn = false;
			round++;
			userPlay();
		}

		else if(lastRoll == 1)
		{
			if(diceRoll == 1)
			{
				printf("%c rolled a %d twice\n", names[PLAYER2], diceRoll);
				printf("All points gone\n");
				scores[PLAYER2] = 0;
				roundScore = 0;
				whoseTurn = false;
				round++;
				userPlay();
			}
			else if(diceRoll == 6)
			{
				printf("Total points double");
				scores[PLAYER2] *= 2;
			}
			
		}
		
		else
		{
			roundScore += diceRoll;
			lastRoll = diceRoll;
			scores[PLAYER2] += roundScore;
			printf("CPU score: %d\n", scores[PLAYER2]); //Debugging
		}
		printScores();
		printf("Round: %d\n",round);
		printf("%c rolled a %d\n", names[PLAYER2], diceRoll);
		printf("Total score is %d\n",scores[PLAYER2]);
		printf("Current round score is %d\n", roundScore);
		printf("Roll again?\n");
		timeUp += generateRandNumber();
	}while(timeUp < 16);

	if(timeUp >= 16)
	{
		if(scores[PLAYER2] >= 100)
		{
			won();
		}
		else
		{
			printf("It is user's turn again\n");
			whoseTurn = false;
			round++;
			userPlay();
		}
	}
}


void userPlay()
{
	printScores();
	static int round = 1;
	int roundScore = 0;
	int lastRoll = 0;
	int diceRoll;
	char decision[3] = "yes";

	printf("Round: %d\n",round);
	do
	{
		//printScores();
		diceRoll = generateRandNumber();
		if(scores[PLAYER1] >= 100)
		{
			won();
		}

		else if(diceRoll == 2)
		{
			printf("%c rolled a %d\n", names[PLAYER1], diceRoll);
			printf("You have lost your points for this round\n");
			roundScore = 0;
			whoseTurn = true;
			round++;
			computerPlay();
		}

		else if(lastRoll == 1)
		{
			if(diceRoll == 1)
			{
				printf("You rolled a %d twice. All points gone\n", diceRoll);
				scores[PLAYER1] = 0;
				roundScore = 0;
				lastRoll = 0;
				whoseTurn = true;
				round++;
				computerPlay();
			}
			else if(diceRoll == 6)
			{
				printf("Total points double");
				scores[PLAYER1] *= 2;
			}
		}

		else
		{
			roundScore += diceRoll;
			lastRoll = diceRoll;
			scores[PLAYER1]+= roundScore;
		}
		printScores();
		printf("Round: %d\n",round);
		printf("%c rolled a %d\n", names[PLAYER1], diceRoll);
		printf("Total score is %d\n",scores[PLAYER1]);
		printf("Current round score is %d\n", roundScore);
		printf("Roll again?\n");
		scanf(" %s", decision);
		//decision = getchar();
	}while(strcmp(decision,"yes") == 0);

	if(strcmp(decision, "no") == 0)
	{
		if(scores[PLAYER1] >= 100)
		{
			won();
		}
		else
		{
			whoseTurn = true;
			round++;
			computerPlay();
		}
	}
}


void play()
{
	if(whoseTurn == false)
	{
		//printf("User player turn\n");
		userPlay();
	}
}


void printScores()
{ 
	printf("_____________________________\n");
	for(int i = 0; i < PLAYERS; i++)
	{
		printf("%c: %d\n",names[i], scores[i]);
	}
}

void won()
{
	if(whoseTurn == false)
	{
		printf("________________________________\n");
		printf("The winner is %c with a score of %d\n",names[PLAYER1], scores[PLAYER1]);
		//printScores();
		exit(1);
	}
	else
	{
		printf("________________________________\n");
		printf("The winner is %c with a score of %d\n",names[PLAYER2], scores[PLAYER2]);
		//printScores();
		exit(1);
	}
}

int main()
{
	printf("Welcome to Pig Game\n");
	printf("______________________________\n");
	printf("Enter the first char of your name\n");
	names[PLAYER2] = 'C';
	scanf(" %c", &names[PLAYER1]);
	//names[PLAYER1] = getchar();
	whoseTurn = false; //Set player turn to player 1
	scores[PLAYER1] = 0;
	scores[PLAYER2] = 0;
	play();
}