#ifndef DEFINES_H
#define DEFINES_H
#include <stdlib.h>
#include <linux/inotify.h>
#define MAX_STRING_LENGTH 500
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define ERROR	-1
#define OK		1
#define MAX_EVENT_LOG_STRING	1000
#endif
