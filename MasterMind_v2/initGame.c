//initGame.c - Peter Nagy
//This function does set the sceen by creating the random
//choices by category as follows:
//	1->easy=>4 colours with no repeats or blank spaces
//	2->medium=>4 colours with repeats, but no blank spaces
//	3->hard=>4 colours with repeats and blanks spaces

#include "MasterMind.h"

void initGameRandom(int gameType);
void createRandom(int *choices, unsigned int size);

/*returns a random int[4] array*/
void initGameRandom(int gameType){
	int easyChoices[7] = {0, 1, 2, 3, 4, 5, 6};
	int mediumChoices[14] = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
	int hardChoices[14] = {0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7};

	switch (gameType)
	{
		case 3:
			createRandom(hardChoices, 14);
			break;
		case 2:
			createRandom(mediumChoices, 14);
			break;
		default:
			createRandom(easyChoices, 7);
			break;
	}

}//end main()

/*createRandom: takes int array and sets iarr4CompChoices[i] with 4 random number, as per selected level*/
void createRandom(int *choices, unsigned size){
	int *choicesCopy = malloc(sizeof(int) * size);
	memcpy(choicesCopy, choices, sizeof(int) * size);
	unsigned int n, i, temp;
	//int iarr4CompChoices[4]; //pushed this into MasterMind.h

	for (int i = size - 1; i >= 0; i--)
	{
		do{
			srand(time(NULL));
			n = rand() % (i +1);
		} while (n > 16);//tbh I don't know why n on the first run[of for] is a massive 6 digit number => loop to avoid it 
		temp = choicesCopy[i];
		choicesCopy[i] = choicesCopy[n];
		choicesCopy[n] = temp;
		if (i < 4)
			iarr4CompChoices[i] = choicesCopy[i];
	}//end for (int i = size - 1; i > 0; i--)

#ifdef DEBUG
	printf("\n=====DEBUG\n===== The random color values/colors are: \n\t");
	for (int j = 0; j < 4; ++j)
		printf("%d / %s, ", iarr4CompChoices[j]+1, COLORS[iarr4CompChoices[j]]);//this show the game choices npt the array positions
	putchar('\n');
#endif
}//end createRandom(int *choices, unsigned size)