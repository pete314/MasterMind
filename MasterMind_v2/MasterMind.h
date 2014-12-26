/*
*	MasterMind.h - the main header for mastermind - by Peter Nagy 
*/

#ifndef __MasterMind_h__
#define __MasterMind_h__

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//#define DEBUG
//#define HARDCORE_DEBUG // :) :)

#define MAX_CHARS 10000
#define CHOICES_PER_ROUND 4
#define CONSOLE_OUTPUT "MasterMind> "
#define CORRECT_MARKER 1
#define INCORRECT_MARKER 111
#define HELPER_FILE "help.dat"
#define GAMEPLAY_TEXT_FILE_NAME "screenText.dat"
#define GAME_STATS_FILE_NAME "gameStats.dat"

typedef enum{ false, true} bool;
extern struct Stat{
	char userName[200];
	int selectedRounds;
	int playedRounds;
	int correctLocation;
	int correctColor;
	double gameTime;
} currentGameStat;

static const char *COLORS[] = { "Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet", "Blank" };
extern int iarr4CompChoices[4];
extern char gamePlayTextHolder[MAX_CHARS];
extern char charr200UserName[200];

#endif