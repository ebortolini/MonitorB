#ifndef LOG_EVENT_H
#define LOG_EVENT_H
#include <stdio.h>
FILE * OpenFile(unsigned char * FileName, unsigned char * Mode);

int LogEvent(char * Message);
int CloseFile(FILE * FileToClose);

#endif
