#include "Queue.h"
#include "DataTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


TargetToMonitor * CreateNode(){
	TargetToMonitor * NewNode;
	NewNode = (TargetToMonitor *)malloc(sizeof(TargetToMonitor));
	if(!NewNode){
		//TODO: Put an log here
		return NULL;
	}
	return NewNode;
}

int initData(TargetToMonitor * Node, Info * info){
	if(!Node)
		return -1;
	Node->Next = NULL;
	Node->Flags = info->Flags;
	Node->InitHandle = info->InitHandle;
	strcpy(Node->DictoryName,info->Directory);
	return 1;

}

TargetToMonitor * AddNewNode(TargetToMonitor * QueueOfTargets, Info * info){
	TargetToMonitor * AuxTarget;
	//if(Info)
		//return NULL;
	if(!QueueOfTargets){
		AuxTarget = CreateNode();
		if(!AuxTarget)
			return NULL;
		initData(AuxTarget, info);
		return AuxTarget;
	}
	AuxTarget = QueueOfTargets;
	while(AuxTarget->Next != NULL)
		AuxTarget = AuxTarget->Next;
	AuxTarget->Next = CreateNode();
	AuxTarget = AuxTarget->Next;
	if(!AuxTarget)
		return NULL;
	initData(AuxTarget, info);
	return QueueOfTargets;
}

void printQueueInfo(TargetToMonitor * QueueOfTargets){
	TargetToMonitor * AuxTarget = QueueOfTargets;
	while (AuxTarget){
		printf("\n\tDir Name: %s", AuxTarget->DictoryName);
		AuxTarget = AuxTarget->Next;
	}
}
