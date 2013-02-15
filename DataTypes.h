#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include "Defines.h"

typedef struct SInfo{
	char Directory[MAX_STRING_LENGTH];
	int  InitHandle;
}Info;

/*
 * Our struct
 */
typedef struct STargetToMonitor{
	char DictoryName[MAX_STRING_LENGTH];
	int  InitHandle;
	int WatchHandle;
	struct STargetToMonitor * Next;
}TargetToMonitor;

#endif
