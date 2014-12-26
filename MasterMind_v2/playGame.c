//playGame.c - Peter Nagy
#include "MasterMind.h"

//void createRandom(int *choices, unsigned int size);
//extern void initGameRandom(int gameType);
//void createHeader(void);
void playGame(int, int);
int checkPrintCorrectGuesses(int iarr4UserRoundColorChoice[]);
void getUserSelectionForColors(int *iarr4RoundChoices, int ceiling, int header);
int getUserSelections(int questionNo, int floor, int ceiling);
void readHeader(int);
int printDoExit(void);

//global variables
int iarr4CompChoices[4];
char gamePlayTextHolder[MAX_CHARS];

//playGame_main: This function does control the gameplay.
/*	->Possible startin options are from console[with level & no. rounds] if so skip to no.4
	->It does the following steps:
		1.) Game intro
		2.) Level selector
			2.1.) Generate random colors [this is done even if console startin]
		3.) Round selector
		4.) Start game play
		5.) Get user choices for rounds
		6.) Check for results [win:lose]
		7.) Replay option
*/
void playGame_main(int iStartLevel, int iStartRounds){
	int iNumOfRounds, iRoundCnt, iLevelNo, iLevelColorChoiceQuestion;
	int iCnt, iCeilingColorChoice;
	int iarr4UserRoundColorChoice[CHOICES_PER_ROUND];
#ifdef DEBUG
	system("color 0a"); //just making it obvious
#endif
#ifdef HARDCORE_DEBUG
	system("color 0c"); //just making it even more obvious
#endif
	
	iLevelNo = 0;

	// 1.) Game intro {only if not console startin
	if (iStartLevel != 0 || iStartRounds != 0)
		readHeader(0);//game intro
	
	do{
		if (iLevelNo != 0)
			system("cls");//this means it's second game so clear the previous things from screen
		readHeader(1);//level selector intro
		//Initialize the game if not done yet
		//2.) Level selector
		iLevelNo = (iStartLevel > 0) ? iStartLevel : getUserSelections(99, 1, 3);
		
		//2.1.) Generate random colors [this is done even if console startin]
		initGameRandom(iLevelNo);
		
		//3.) Round selector
		iNumOfRounds = (iStartRounds > 0) ? iStartRounds : getUserSelections(2, 5, 15);

		system("cls");
		//Zero the game statistics
		initNewGameStat(iNumOfRounds);
		/*REFACTOR THIS INTO A *CHAR[], += NEW ROW RESULT RETURN ARRAY*/
		//4.) Start game play
		readHeader(5);
		printf("\t\t\t%d Rounds on Level %d", iNumOfRounds, iLevelNo);

		if (iLevelNo <= 2){
			iLevelColorChoiceQuestion = 3;
			iCeilingColorChoice = 7;
		}
		else{
			iLevelColorChoiceQuestion = 4;
			iCeilingColorChoice = 8;
		}//end (iLevelNo <= 2)

		//5.) Get user choices for rounds
		iRoundCnt = 0;
		do{
			printf("\n[Round %d]", iRoundCnt + 1);
			getUserSelectionForColors(iarr4UserRoundColorChoice, iCeilingColorChoice, iLevelColorChoiceQuestion);//iarr4UserRoundColorChoice[iUserRoundColorChoiceCnt] = getUserSelections(5, 1, 7);
			if (checkPrintCorrectGuesses(iarr4UserRoundColorChoice))
				break;
		} while (++(iRoundCnt) != iNumOfRounds);
		(iNumOfRounds == iRoundCnt) ? readHeader(7) : readHeader(8);// 6.) Check for results[win:lose]
		storeRoundResults();
	} while (getUserSelections(6, 1, 2) != 2);
	
	readHeader(9);
	Sleep(2000);
	exit(0);
}//end main()

//checkPrintCorrectGuesses: function has 3 parts:
/*		1.) print user choice
		2.) compare with random generated
		3.) print user a hint of positions
*/
int checkPrintCorrectGuesses(int iarr4UserRoundColorChoice[]){
	int iCnt, iCorrectGuesses, iCGueesNCorrectLoc, iGenCnt, jCnt;
	bool isWinner = false;

	// 1.) print user choice
	printf("\nYou choose: ");
	for (iCnt = 0; iCnt < CHOICES_PER_ROUND; ++iCnt)
		printf("\t%-10s", COLORS[iarr4UserRoundColorChoice[iCnt]]);
	putchar('\n');

#ifdef DEBUG
	printf("To Win choose:");
	for (iCnt = 0; iCnt < CHOICES_PER_ROUND; ++iCnt)
		printf("\t%-10s | ", COLORS[iarr4CompChoices[iCnt]]);
	putchar('\n');
#endif

	// 2.) compare with random generated
	iCorrectGuesses = iCGueesNCorrectLoc = 0;
	iGenCnt = - 1;
	while (++(iGenCnt) != CHOICES_PER_ROUND){
		if (iarr4UserRoundColorChoice[iGenCnt] == iarr4CompChoices[iGenCnt])
			++iCorrectGuesses;
		else{
			for (jCnt = 0; jCnt != CHOICES_PER_ROUND; ++jCnt)
				if (iarr4UserRoundColorChoice[iGenCnt] == iarr4CompChoices[jCnt])
					++iCGueesNCorrectLoc;
		}
	}//end while (++(iGenCnt) != CHOICES_PER_ROUND)

	// 3.) print user a hint of positions
	printf("Correct Guesses on Correct Location: %d [%c]\n", iCorrectGuesses, 1);
	printf("Correct Guesses not Correct Location: %d [%c]\n", iCGueesNCorrectLoc, 2);
	
	// increment the stat counters
	currentGameStat.correctLocation += iCorrectGuesses;
	currentGameStat.correctColor += iCGueesNCorrectLoc;
	currentGameStat.playedRounds++;

	if (iCorrectGuesses == 4)
		isWinner = true;

	do{
		if (iGenCnt % 2 == 0)
			printf("\n %-39s", " ");//just center in a 2/2 layout
		else
			putchar(' ');
		if (--iCorrectGuesses >= 0)
			printf("%c ", 1);
		else if (--iCGueesNCorrectLoc >= 0)
			printf("%c ", 2);
	} while (--iGenCnt != 0);
	putchar('\n');
	return isWinner;
}//checkPrintCorrectGuesses(void)

/*getUserSelectionForColors: REFACTOR THIS FUNCTION => getUserSelection*/
void getUserSelectionForColors(int iarr4RoundChoices[], int ceiling, int headerNo){
	int iInputNum, iRoundCnt, iCorrectCnt;
	readHeader(headerNo);
	
	for (iRoundCnt = 1; iRoundCnt < 5; ++iRoundCnt){
		printf("%s [Color %d] ", CONSOLE_OUTPUT, iRoundCnt);
		for (;;){
			fflush(stdin);
			scanf(" %d", &iInputNum);
			if (iInputNum >= 1 && iInputNum <= ceiling)
				break;
			else if (iInputNum == 0)
				printDoExit();
			printf("%s [Color %d] ", CONSOLE_OUTPUT, iRoundCnt);
		}//end for(;;)
		iarr4RoundChoices[iRoundCnt - 1] = iInputNum-1;
	}//end for (iRoundCnt = 1; iRoundCnt < 5; ++iRoundCnt)
}//end int getUserSelectionForColors(int iRoundCnt)

/*getUserSelection: get user input for some question and handle*/
int getUserSelections(int questionNo, int floor, int ceiling){
	int iInputNum;
	readHeader(questionNo);
	printf(CONSOLE_OUTPUT);

	while (1){
		scanf("%d", &iInputNum);
		if (iInputNum >= floor && iInputNum <= ceiling){
#ifdef DEBUG
			printf("User selected %d, is between %d and %d: ", iInputNum, floor, ceiling);
#endif
			fflush(stdin);
			break;
		}
		if (iInputNum == 0){
			printDoExit();
		}//end if (iInputChar == 'q' || iInputChar == 'Q')
		
		fflush(stdin);
		printf(CONSOLE_OUTPUT);
	}//end while (c = getchar())
	
	return iInputNum;
}//end getUserSelections()

/*readHeader: reads the header file content(if needed), pulls out the the section identified by section number*/
void readHeader(int getSection){
	bool inComment = false;
	int iInputChar, iLastChar, iCnt_i, iSectionCnt;

	//init vars
	iCnt_i = iInputChar = 0;
	iSectionCnt = -1;
	iLastChar = 124; // ascii | for nice output
	
	if (gamePlayTextHolder[0] == NULL)
		readFile(GAMEPLAY_TEXT_FILE_NAME, gamePlayTextHolder);

	while ((iInputChar = gamePlayTextHolder[iCnt_i++]) != EOF){
		if (iInputChar == '*' && iLastChar == '/'){
			inComment = true;
			iSectionCnt = gamePlayTextHolder[iCnt_i] - '0';//((fileTextHolder[iCnt_i] - '0') * 10) + (fileTextHolder[++iCnt_i] - '0');//after // (the next number*10)+nextNumber which gives a two digit number
#ifdef HARDCORE_DEBUG
			printf("\nsection found: %d", iSectionCnt);
			if (getSection != iSectionCnt)
				printf("<-Section finder works but not the one we looking for\n");
#endif
		}
		else if (iLastChar == '*' && iInputChar == '/'){
			inComment = false;
			iLastChar = ' ';
			continue;
		}
		if ((inComment == false) && (getSection == iSectionCnt))
			putchar(iLastChar);

		iLastChar = iInputChar;
	}//end while ((ch = fgetc(fp)) != EOF)
}//end readHeaderFile(int getSection)



/*printDoExit: get approval for exit*/
int printDoExit(void){
	char cQuestion[] = { "\n>>>>>>>>>>>>>>>>>>>>> n) No y) Yes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" };
	int iUserChoice;

	printf("\n********************************************************************************");
	printf("\n******************* You enter 0 for exit are you sure?**************************");
	printf(cQuestion);
	printf(CONSOLE_OUTPUT);

	do{
		
		iUserChoice = getchar();
		if (iUserChoice == 'y' || iUserChoice == 'Y'){
			readHeader(9);
			Sleep(3000);//just give a chance to user to realize, the choice of leaving the game & before say bye :)
			exit(0);
		}
		else if (iUserChoice == 'n' || iUserChoice == 'N'){
			break;
		}
		if (iUserChoice == '\n')
			printf(CONSOLE_OUTPUT);
	} while (1);

	return 1;
}//printDoExit()