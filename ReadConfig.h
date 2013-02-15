#ifndef READ_CONFIG_H
#define READ_CONFIG_H
#include <stdlib.h>
#include <stdio.h>
#include "DataTypes.h"
/*
 * Function Name: ReadLine
 * Input:
 * File: Pointer to file to read content
 * Line: Pointer to string where to put the content from one line of the file
 * Output:
 * Return the number of characters read
 */
int ReadLine(FILE * File, char * Line);

/*
 * Function Name: ReadLine
 * Output:
 * Return a list of directories to monitor
 */
TargetToMonitor *  readFile(Info * Info);
#endif
