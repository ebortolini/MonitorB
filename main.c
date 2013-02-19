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
	char buffer[EVENT_BUF_LEN];
	int i;
	int length;
	TargetToMonitor *Target;
	Info Info;
	Info.InitHandle = IoNotifyInit();
	if(Info.InitHandle < 0)
	{
		printf("\n\tError");
	}
	Info.Flags = IN_CREATE | IN_DELETE;
	if(Info.InitHandle < 0)
		return -1;
	Target = readFile(&Info);
	printQueueInfo(Target);
	InstallWatchers(Target);

	struct timeval time;
	int ret;
	setbuf(stdout, NULL);
	while(1){
		setbuf(stdout, NULL);
		ret = HasEvents(Info.InitHandle, 2);
		if (ret < 0)
			return -1;
		else{

		ProcessEvent(&Info, Target);
		}
			/*
			length = read( Info.InitHandle, buffer, EVENT_BUF_LEN );

				if ( length < 0 ) {
					perror( "read" );
				}
					i =0;


						  while ( i < length ) {
							  struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
							  if ( event->len ) {
							  if ( event->mask & IN_CREATE ) {
								if ( event->mask & IN_ISDIR ) {
								  printf( "New directory %s created.\n", event->name);
								}
								else {
								  printf( "New file %s created.\n", event->name );
								}
							  }
							  else if ( event->mask & IN_DELETE ) {
								if ( event->mask & IN_ISDIR ) {
								  printf( "Directory %s deleted.\n", event->name );
								}
								else {
								  printf( "File %s deleted.\n", event->name );
								}
							  }
							}
							i += EVENT_SIZE + event->len;
						  }
		}
		*/
	}


	  /*removing the “/tmp” directory from the watch list.*/
	   //inotify_rm_watch( fd, wd );
	RemoveWatcher(Target);

	  /*closing the INOTIFY instance*/
	   close( Info.InitHandle );

	return 1;
}
