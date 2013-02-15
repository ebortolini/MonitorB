#include "Queue.h"
#include "DataTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TargetToMonitor * AddNewNode(TargetToMonitor * QueueOfTargets, Info * info){
	TargetToMonitor * AuxTarget;
	//if(Info)
		//return NULL;
	if(!QueueOfTargets){
		AuxTarget = (TargetToMonitor *) malloc(sizeof(TargetToMonitor));
		strcpy(AuxTarget->DictoryName, info->Directory);
		AuxTarget->InitHandle = info->InitHandle;
		AuxTarget->Next = NULL;
		return AuxTarget;
	}
	AuxTarget = QueueOfTargets;
	while(AuxTarget->Next != NULL)
		AuxTarget = AuxTarget->Next;
	AuxTarget->Next = (TargetToMonitor *) malloc(sizeof(TargetToMonitor));
	AuxTarget = AuxTarget->Next;
	AuxTarget->Next = NULL;
	strcpy(AuxTarget->DictoryName, info->Directory);
	return QueueOfTargets;
}

void printQueueInfo(TargetToMonitor * QueueOfTargets){
	TargetToMonitor * AuxTarget = QueueOfTargets;
	while (AuxTarget){
		printf("\n\tDir Name: %s", AuxTarget->DictoryName);
		AuxTarget = AuxTarget->Next;
	}
}
