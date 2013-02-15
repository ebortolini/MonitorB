#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/inotify.h>
#include "Defines.h"
#include "DataTypes.h"
#include "Queue.h"
#include <string.h>
#include <assert.h>
#include "ReadConfig.h"

char const * GlobalFileName = "MonitorB.cfg";

int ReadLine(FILE * File, char * Line){
	if(File == NULL || Line == NULL)
		return -1;
	char ch;
	int counter = 0;
	while( ( ch = fgetc(File) ) != '\n' && ch != EOF ){
		//printf("%c",ch);
		Line[counter++] = ch;
	}
	Line[counter] = '\0';
	return counter;
}

TargetToMonitor *  readFile(Info * Info){
	FILE * File = fopen(GlobalFileName,"r");
	char FileName[MAX_STRING_LENGTH];
	TargetToMonitor * NewTarget = NULL;
	//Info info;
	if( File == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	while (ReadLine(File,FileName) > 0){
		//printf("\nThe contents of file are: %s\n", FileName);
		strcpy(Info->Directory, FileName);
		NewTarget = AddNewNode(NewTarget, Info);
		assert(NewTarget!=NULL);
	}
	fclose(File);
	return NewTarget;
}


