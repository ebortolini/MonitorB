#include <stdlib.h>
#include "Queue.h"
#include "ReadConfig.h"
#include <linux/inotify.h>

int main(){
	TargetToMonitor *Target;
	Info Info;
	Info->InitHandle = IoNotifyInit();
	if(Info->InitHandle < 0)
		return -1;
	Target = readFile(&Info);
	printQueueInfo(Target);
	return 1;
}
