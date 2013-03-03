#include "LogEvent.h"
#include <stdio.h>
#include "Defines.h"
char const * ConfigurationFile = "/var/MonitorB/logs";
FILE * OpenFile(unsigned char * FileName, unsigned char * Mode){
	if(!FileName || !Mode)
		return NULL;
	FILE * newFile = fopen(FileName,Mode);
	return newFile;
}

int LogEvent(char * Message){
	if(!Message)
		return ERROR;
	FILE * FileToLog = OpenFile(ConfigurationFile, "a+");
	if(!FileToLog)
		return ERROR;
	fprintf(FileToLog,"%s\n",Message);
	CloseFile(FileToLog);
	return OK;
}

int CloseFile(FILE * FileToClose){
	fclose(FileToClose);
}
