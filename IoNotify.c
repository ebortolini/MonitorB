#include "IoNotify.h"
#include "DataTypes.h"
#include <linux/inotify.h>
int IoNotifyInit(){
	return inotify_init();
}

//wd = inotify_add_watch( fd, "/tmp", IN_CREATE | IN_DELETE );

int AddWatcher(TargetToMonitor * Target, int Flags){
	if(!Target || !Flags)
		return -1;
	Target->WatchHandle = inotify_add_watch(Target->InitHandle,
			Target->DictoryName,Flags);
	if (Target->WatchHandle < 0)
		return -1;
	return 1;

}

int InstallWatchers(TargetToMonitor * Queue){

}
