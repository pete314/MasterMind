//gameUtils.c - Peter Nagy

#include "MasterMind.h"

void readFile(char **, char*);
void writeStats2File(char **filaName, struct Stats *);

/*readFile: reads a file into var/memory pointer*/
void readFile(char **fileName, char *varCharPointer){
	FILE *fp;
	int iCnt_i, iInputChar;

	iCnt_i = iInputChar = 0;

	fp = fopen(fileName, "r"); // read mode
	if (fp == NULL)
	{
		perror("A core file is missing(or can't open)\nThe application will exit now");
		Sleep(3);
		exit(EXIT_FAILURE);
	}

	while ((iInputChar = fgetc(fp)) != EOF)
		varCharPointer[iCnt_i++] = iInputChar;//just copy the file content to "memory" for performance
	varCharPointer[iCnt_i++] = '\0';
	fclose(fp);
}//end readFile(void)

void writeStats2File(char **fileName, struct Stat *data){
	FILE *fp = fopen(fileName, "a");// apend

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");//u could use printf here

	fprintf(fp, "%s %c", data->userName, '\t');
	fprintf(fp, "%d %c", data->correctColor, '\t');
	fprintf(fp, "%d %c", data->correctLocation, '\t');
	fprintf(fp, "%d %c", data->playedRounds, '\t');
	fprintf(fp, "%d %c", data->selectedRounds, '\t');
	fprintf(fp, "%f %c", data->gameTime, '\n');

	fclose(fp);
}//end writeFile(char **filaName, void *data)