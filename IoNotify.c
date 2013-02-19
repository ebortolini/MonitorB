#include "DataTypes.h"
#include <linux/inotify.h>
#include <assert.h>
#include "IoNotify.h"

int IoNotifyInit(){
	return inotify_init();
}

//wd = inotify_add_watch( fd, "/tmp", IN_CREATE | IN_DELETE );

int AddWatcher(TargetToMonitor * Target){
	if(!Target )
		return -1;
	Target->WatchHandle = inotify_add_watch(Target->InitHandle,
			Target->DictoryName,Target->Flags);
	if (Target->WatchHandle < 0)
		return -1;
	return 1;

}

void RemoveWatcher(TargetToMonitor * Queue){
	TargetToMonitor * AuxQueue = Queue;
	while(AuxQueue){
		inotify_rm_watch(AuxQueue->InitHandle, AuxQueue->WatchHandle);
		AuxQueue = AuxQueue->Next;
	}
}

int InstallWatchers(TargetToMonitor * Queue){
	TargetToMonitor * AuxQueue = Queue;
	int ReturnedValue;
	while(AuxQueue){
		ReturnedValue = AddWatcher(AuxQueue);
		assert(ReturnedValue != -1);
		if(ReturnedValue < 0){
			return -1;
		}
		AuxQueue = AuxQueue->Next;
	}
	return 1;
}
