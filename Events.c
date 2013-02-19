#include <unistd.h>
#include <sys/select.h>
#include "DataTypes.h"
#include "Defines.h"
#include "stdlib.h"
#include "Events.h"
#include <string.h>
#include <stdio.h>
int HasEvents(int Handle, int TimeOut){
	fd_set rfds;
	FD_ZERO (&rfds);
	struct timeval Time;
	Time.tv_sec = TimeOut < 1 ? 1 : TimeOut;
	Time.tv_usec = 0;
	FD_SET (Handle, &rfds);
	return select (FD_SETSIZE, &rfds, NULL, NULL, &Time);

}

void printEvents(Event * Queue){
	Event * Aux = Queue;
	while(Aux){
		printf("\n\tEvent Name: %s",Aux->InotifyEvent->name);
		Aux = Aux->Next;
	}
}

Event * CreateEvent(){
	return (Event *)malloc(sizeof(Event));
}

Event * EnqueueEvent(struct inotify_event* InotifyEvent, Event * QueueOfEvents){
	if(!InotifyEvent)
		return NULL;
	Event * Aux;
	if(!QueueOfEvents){
		Aux = CreateEvent();
		Aux->InotifyEvent = InotifyEvent;
		Aux->Next = NULL;
		return Aux;
	}
	Aux = CreateEvent();
	Aux->InotifyEvent = InotifyEvent;
	Aux->Next = NULL;
	QueueOfEvents->Next = Aux;
	return QueueOfEvents;
}

Event * ReadEvents(Info * info, char * Buffer){
	int counter = 0;
	struct inotify_event *InotifyEvent;
	Event * QueueOfEvents = NULL;
	int length = read( info->InitHandle, Buffer, EVENT_BUF_LEN );
	while(counter < length){
		InotifyEvent = ( struct inotify_event * ) &Buffer[ counter ];
		QueueOfEvents = EnqueueEvent(InotifyEvent, QueueOfEvents);
		counter = EVENT_SIZE + InotifyEvent->len;
	}
	return QueueOfEvents;
}

TargetToMonitor * GetTarget(int Descriptor, TargetToMonitor * Targets){
	if(!Targets || Descriptor < 0)
		return NULL;
	TargetToMonitor * AuxTarget = Targets;
	while(AuxTarget){
		if(AuxTarget->WatchHandle == Descriptor)
			return AuxTarget;
		AuxTarget = AuxTarget->Next;
	}
	return NULL;
}



int WriteEvent(Event * EventToWrite, TargetToMonitor * TargetOfEVent){
	if(!EventToWrite || !TargetOfEVent)
		return 1;
	if (EventToWrite->InotifyEvent->mask & IN_CREATE){
		if(EventToWrite->InotifyEvent->mask & IN_ISDIR)
			printf("\n\tNew Directory Created. Name: %s , In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
	}
	return 1;
}

void LogEvents(Event * QueueOfEVents, TargetToMonitor * Targets){
	if(!QueueOfEVents)
		return;
	TargetToMonitor * Target;
	Event * AuxQueue = QueueOfEVents;
	while(AuxQueue){
		Target = GetTarget(AuxQueue->InotifyEvent->wd, Targets);
		if(Target){
			WriteEvent(AuxQueue,Target);
			printf("\n\tEvent: %s on Dir: %s",AuxQueue->InotifyEvent->name,
					Target->DictoryName);
		}
		AuxQueue = AuxQueue->Next;
	}
}

int ProcessEvent(Info * info,TargetToMonitor* Queue){
	Event *QueueOfEvents = NULL;
	char Buffer[EVENT_BUF_LEN];
	QueueOfEvents = ReadEvents(info, Buffer);
	printEvents(QueueOfEvents);
	LogEvents(QueueOfEvents,Queue);
	return 0;
}
