//gameStats.c - Peter Nagy
#include "MasterMind.h"

void initNewGameStat(int);
void storeRoundResults();
void printSatats();

struct Stat currentGameStat;
time_t startTime;
time_t endTime;

/*initNewGameState: does reset the currentGameStat struct and start game timer*/
void initNewGameStat(int roundNum){
	currentGameStat.correctColor = 0;
	currentGameStat.correctLocation = 0;
	currentGameStat.gameTime = 0;
	currentGameStat.playedRounds = 0;
	currentGameStat.selectedRounds = roundNum;
	if (strlen(charr200UserName) == 0)
		strcpy(currentGameStat.userName, "Anonymous");
	else
		strcpy(currentGameStat.userName, charr200UserName);

	startTime = time(0);
}//end initNewGameStat(int roundNum)

/*storeRoundResults: store game results in file, and stop timer*/
void storeRoundResults(){
	endTime = time(0);
#ifdef DEBUG
	printf("Time elapsed: %.0f ", difftime(endTime, startTime));
#endif
	currentGameStat.gameTime = difftime(endTime, startTime);//gives seconds
	
	//write data to file
	writeStats2File(GAME_STATS_FILE_NAME, &currentGameStat);
	
	printSatats();
}//end void storeRoundResults()

/*printStats(): print the last gameplay statistics */
void printSatats(){
	puts("********************** Game Statistics ***************************************");
	printf("Username: %s\nSelected Rounds: %d\nCorrect Color: %d\nCorrect Location: %d\nIn Game: %.0f seconds\n", 
				currentGameStat.userName, currentGameStat.selectedRounds, currentGameStat.correctColor, currentGameStat.correctLocation, currentGameStat.gameTime);
}//end printStats()


void readPrintStat(){
	FILE *fp = fopen(GAME_STATS_FILE_NAME, "r");
	int i = 0;

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");
	else
		puts("User Name | Correct Color | Correct Color&Location | Rounds Played | Game Time\n");

	while (!feof(fp)){
		struct Stat *tmpInputStat = (struct Stat*)malloc(sizeof(struct Stat));
		fscanf(fp, "%s", tmpInputStat->userName);
		
		//This is just a general check if the username is more than 50chars long don't print
		if (strlen(tmpInputStat->userName) < 50){
			fscanf(fp, "%d", &tmpInputStat->correctColor);
			fscanf(fp, "%d", &tmpInputStat->correctLocation);
			fscanf(fp, "%d", &tmpInputStat->playedRounds);
			fscanf(fp, "%d", &tmpInputStat->selectedRounds);
			fscanf(fp, "%lf", &tmpInputStat->gameTime);

			printf("%-11s %-16d %-24d %-14d %2.1f \n", tmpInputStat->userName, tmpInputStat->correctColor, tmpInputStat->correctLocation, tmpInputStat->playedRounds, tmpInputStat->gameTime);
		}
		else
			break;	
	}
	fclose(fp);
	exit(1);
}//end readPrintStat()
