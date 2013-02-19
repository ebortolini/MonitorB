#ifndef EVENTS_H
#define EVENTS_H
#include <unistd.h>

typedef struct SEvent{
	struct inotify_event * InotifyEvent;
	struct SEvent * Next;
}Event;
int HasEvents(int Handle, int TimeOut);

int ProcessEvent(Info * info,TargetToMonitor* Queue);
#endif

