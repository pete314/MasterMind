//startGame.c - the game starts here :)

#include "MasterMind.h"

void startGame(int, int);
void showHelp();

extern void playGame_main(int *, int *);
extern void readPrintStat();

char charr200UserName[200];

main(int argc, char *argv[]){
	/**
		Startup options are:
		-u, --user: set username
		-l, --level: set level between 1 & 3
		-r, --round: set num of rounds to play between 5 & 15
		-s, --stat: show statistics
		-h, --help: show help for startup
		-i, --intro: show game play details
		-a, --about: game creator credentials
	*/
	int iCnt = 1,
		iStartLevel = 0,
	    iStartRound = 0;

	//startGame(&iStartLevel, &iStartRound);
	if (argc < 2)
		showHelp();
	else{
#ifdef HARDCORE_DEBUG
		printf("\n CMD passed param cnt: %d \n", argc);
#endif
		while (argc >= iCnt){
			if (strcmp(argv[iCnt], "-h") == 0
				|| strcmp(argv[iCnt], "--help") == 0)
				showHelp();
			else if (strcmp(argv[iCnt], "-u") == 0){
				if (argc > (++iCnt)){
					strcpy(charr200UserName, argv[iCnt]);
					--iCnt;
				}
				else
					showHelp();
			}//end else if (strcmp(argv[iCnt], "-u")
			else if (strcmp(argv[iCnt], "--user") == 0){
				if (argc > (iCnt + 2)){
					strcpy(charr200UserName, argv[++iCnt]);
					strcat(charr200UserName, "_");
					strcat(charr200UserName, argv[++iCnt]);
#ifdef HARDCORE_DEBUG
					printf("after user icnt %d", iCnt);
#endif
					iCnt--;
				}
				else
					showHelp();
			}//end else if (strcmp(argv[iCnt], "--user")
			else if (strcmp(argv[iCnt], "-l") == 0
						|| strcmp(argv[iCnt], "--level") == 0){
				++iCnt;
				if (argc > iCnt 
					&& (atoi(argv[iCnt]) > 0 && atoi(argv[iCnt]) < 4)){
					iStartLevel = atoi(argv[iCnt]);
#ifdef HARDCORE_DEBUG
					printf("iStartLevel: %d argv %d iCnt: %d", iStartLevel, atoi(argv[iCnt]), iCnt);
#endif
					--iCnt;
				}
				else
					showHelp();
			
			}//end else if strcmp(argv[iCnt], "-l")
			else if (strcmp(argv[iCnt], "-r") == 0
				|| strcmp(argv[iCnt], "--round") == 0){
				++iCnt;
				if (argc > iCnt
					&& (atoi(argv[iCnt]) > 4 && atoi(argv[iCnt]) < 16)){
					iStartRound = atoi(argv[iCnt]);
#ifdef HARDCORE_DEBUG
					printf("iStartRound: %d argv %d iCnt: %d", iStartRound, atoi(argv[iCnt]), iCnt);
#endif
					--iCnt;
				}
				else
					showHelp();
			}
			else if (strcmp(argv[iCnt], "-s") == 0
					|| strcmp(argv[iCnt], "--stat") == 0){
				readPrintStat();
			}//end else if (strcmp(argv[iCnt], "-s")
			else if (strcmp(argv[iCnt], "-i") == 0
				|| strcmp(argv[iCnt], "--intro") == 0){
				readHeader(0);
				exit(1);
			}//end else if (strcmp(argv[iCnt], "-i")
			else
				showHelp();

			iCnt += 2;
			if (iCnt >= argc)
				break;//if no other param
		}//end while (argc != iCnt)
		
		startGame(&iStartLevel, &iStartRound);
	}//end if(argc < 2)
	//this is the place of no return :) [not possible to get here]
	exit(1);
}//end main

void startGame(int *iStartLevel, int *iStartRound){
#ifdef DEBUG
	printf("\n\nStarted: %s, level: %d, rounds: %d", charr200UserName, *iStartLevel, *iStartRound);
#endif
	playGame_main(*iStartLevel, *iStartRound);

}//end startGame(int, int)

/*showHelp(): show available command line arguments*/
void showHelp(){
	char tempHelper[MAX_CHARS];
	readFile(HELPER_FILE, tempHelper);
	puts("\n\n\t------{ WHOOPS, THERE WAS AN ERROR! PLEASE CHECK THE START OPTIONS}---\n\n");
	puts(tempHelper);
	Sleep(3000);
	exit(1);
}//end showHelp()

