#ifndef IO_NOTIFY_H
#define IO_NOTIFY_H
#include "DataTypes.h"
#include <linux/inotify.h>
int IoNotifyInit();

int InstallWatchers(TargetToMonitor * Queue);

void RemoveWatcher(TargetToMonitor * Queue);
#endif
