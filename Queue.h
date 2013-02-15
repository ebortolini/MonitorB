#ifndef QUEUE_H
#define QUEUE_H
#include "Defines.h"
#include "DataTypes.h"

TargetToMonitor * AddNewNode(TargetToMonitor * QueueOfTargets, Info * info);

void printQueueInfo(TargetToMonitor * QueueOfTargets);
#endif
