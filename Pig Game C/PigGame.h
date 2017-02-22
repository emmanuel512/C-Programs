/**********************************/
//Emmanuel Banjo
//C Implementation of Pig Game
//PigGame.h
/**********************************/ 

/*******Defines******************/
#define PLAYERS		2 	
#define PLAYER1		0
#define PLAYER2		1

/********Function and Variable Declarations********/
char names[PLAYERS];
unsigned int scores[PLAYERS];
bool whoseTurn;

int generateRandNumber(void);
void play(void);
void userPlay(void);
void computerPlay(void);
void won(void);
void printScores(void);
