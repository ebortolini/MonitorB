#include "Defines.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "Queue.h"
#include "ReadConfig.h"
#include <linux/inotify.h>
#include "IoNotify.h"
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include "Events.h"


int main(){
	int ret;
	TargetToMonitor *Target;
	Info Info;
	Info.InitHandle = IoNotifyInit();
	if(Info.InitHandle < 0)
	{
		printf("\n\tError");
	}
	Info.Flags = IN_CREATE | IN_DELETE | IN_MODIFY | IN_ATTRIB | IN_MOVED_FROM | IN_MOVED_TO;
	if(Info.InitHandle < 0)
		return -1;
	Target = readFile(&Info);
	printQueueInfo(Target);
	ret = InstallWatchers(Target);
	if(ret < 0)
		return -1;

	setbuf(stdout, NULL);
	while(1){
		setbuf(stdout, NULL);
		ret = HasEvents(Info.InitHandle, 2);
		if (ret < 0)
			return -1;
		else if(ret)
			ProcessEvent(&Info, Target);

		sleep(2);
	}


	  /*removing the “/tmp” directory from the watch list.*/
	   //inotify_rm_watch( fd, wd );
	RemoveWatcher(Target);

	  /*closing the INOTIFY instance*/
	   close( Info.InitHandle );

	return 1;
}
