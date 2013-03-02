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
void AddEvent(Event * Queue, Event * Node){
	if(!Queue || !Node)
		return;
	Event * AuxQueue = Queue;
	while(AuxQueue->Next != NULL){
		AuxQueue = AuxQueue->Next;
	}
	AuxQueue->Next = Node;
}
Event * CreateEvent(){
	return (Event *)malloc(sizeof(Event));
}

void DeleteEvent(Event * EventToDelete){
	if(!EventToDelete)
		return;
	free(EventToDelete);
}
Event * EnqueueEvent(struct inotify_event* InotifyEvent, Event * QueueOfEvents){
	if(!InotifyEvent)
		return NULL;
	Event * Aux;
	if(!QueueOfEvents){
		Aux = CreateEvent();
		Aux->InotifyEvent = InotifyEvent;
		Aux->Next = NULL;
		Aux->wasUsed = 0;
		return Aux;
	}
	Aux = CreateEvent();
	Aux->InotifyEvent = InotifyEvent;
	Aux->Next = NULL;
	Aux->wasUsed = 0;
	AddEvent(QueueOfEvents, Aux);
	//QueueOfEvents->Next = Aux;
	return QueueOfEvents;
}

Event * ReadEvents(Info * info, char * Buffer){
	int counter = 0;
	struct inotify_event *InotifyEvent;
	Event * QueueOfEvents = NULL;
	int length = read( info->InitHandle, Buffer, EVENT_BUF_LEN );
	if (length < 0){
		printf("\n\tRead Error");
		return NULL;
	}
	while(counter < length){
		InotifyEvent = ( struct inotify_event * ) &Buffer[ counter ];
		QueueOfEvents = EnqueueEvent(InotifyEvent, QueueOfEvents);
		counter += EVENT_SIZE + InotifyEvent->len;
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

Event * SearchEventByCookie(Event * Queue,int cookie){
	if(!Queue)
		return NULL;
	Event * Aux = Queue;
	while(Aux){
		if(Aux->InotifyEvent->cookie == cookie)
			return Aux;
		Aux = Aux->Next;
	}
	return NULL;
}

int WriteEvent(Event * EventToWrite, TargetToMonitor * TargetOfEVent){
	if(!EventToWrite || !TargetOfEVent)
		return 1;
	if (EventToWrite->InotifyEvent->mask & IN_MOVED_TO && !EventToWrite->wasUsed){
		printf("\n\tMoved: %s", EventToWrite->InotifyEvent->name);
	}
	else if(EventToWrite->InotifyEvent->mask & IN_MOVED_FROM)
	{
		Event * Aux = SearchEventByCookie(EventToWrite->Next, EventToWrite->InotifyEvent->cookie);
		if(!Aux){
			if(EventToWrite->InotifyEvent->mask & IN_ISDIR){
				printf("\n\tDir %s was moved from: %s", EventToWrite->InotifyEvent->name, TargetOfEVent->DictoryName);
			}
			else{
				printf("\n\tFile %s was moved from: %s", EventToWrite->InotifyEvent->name, TargetOfEVent->DictoryName);
			}
		}
		else if(EventToWrite->InotifyEvent->mask & IN_ISDIR){
			printf("\n\tDirectory Moved from %s:, To: %s: In: %s",
					EventToWrite->InotifyEvent->name,Aux->InotifyEvent->name,TargetOfEVent->DictoryName);
			EventToWrite->wasUsed = 1;
		}
		else{
			printf("\n\tFile Moved from %s, to %s, In: %s",
					EventToWrite->InotifyEvent->name,Aux->InotifyEvent->name,TargetOfEVent->DictoryName);
			EventToWrite->wasUsed = 1;
		}
	}
	else if(EventToWrite->InotifyEvent->mask & IN_ATTRIB){
		if(EventToWrite->InotifyEvent->mask & IN_ISDIR){
			printf("\n\tChanged permissions of file: %s in Directory: %s", EventToWrite->InotifyEvent->name,
					TargetOfEVent->DictoryName);
		}

	}
	else if(EventToWrite->InotifyEvent->mask & IN_MODIFY){
		if(EventToWrite->InotifyEvent->mask & IN_ISDIR)
			printf("\n\tFile Modified: Name: %s, In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
	}
	else if (EventToWrite->InotifyEvent->mask & IN_CREATE){
		if(EventToWrite->InotifyEvent->mask & IN_ISDIR)
			printf("\n\tNew Directory Created. Name: %s , In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
		else
			printf("\n\tNew file created: Name: %s, In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
	}
	else if(EventToWrite->InotifyEvent->mask & IN_DELETE){
		if(EventToWrite->InotifyEvent->mask & IN_ISDIR)
			printf("\n\tDirectory deleted. Name: %s , In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
		else
			printf("\n\tFile deleted: Name: %s, In: %s",
					EventToWrite->InotifyEvent->name,TargetOfEVent->DictoryName);
	}
	else{
		printf("\n\tUndefined event: %d", EventToWrite->InotifyEvent->mask);
		printf("\n\tName: %s", EventToWrite->InotifyEvent->name);
	}
	// |  | IN_MODIFY | IN_ATTRIB

	return 1;
}

void LogEvents(Event * QueueOfEVents, TargetToMonitor * Targets){
	if(!QueueOfEVents)
		return;
	TargetToMonitor * Target;
	Event * AuxQueue = QueueOfEVents;
	Event * EventToRemove;
	while(AuxQueue){
		Target = GetTarget(AuxQueue->InotifyEvent->wd, Targets);
		if(Target){
			WriteEvent(AuxQueue,Target);
			/*
			printf("\n\tEvent: %s on Dir: %s",AuxQueue->InotifyEvent->name,
					Target->DictoryName);
			*/
		}
		EventToRemove = AuxQueue;
		AuxQueue = AuxQueue->Next;
		DeleteEvent(EventToRemove);
	}
}

int ProcessEvent(Info * info,TargetToMonitor* Queue){
	Event *QueueOfEvents = NULL;
	char Buffer[EVENT_BUF_LEN];
	QueueOfEvents = ReadEvents(info, Buffer);
	//printEvents(QueueOfEvents);
	LogEvents(QueueOfEvents,Queue);
	return 0;
}
