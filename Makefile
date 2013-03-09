CC = gcc
SOURCES = Events.c IoNotify.c LogEvent.c main.c Queue.c ReadConfig.c
OBJ = $(SOURCES:.c=.o)

MonitorB: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o:%.c
	$(CC) -c -o $@ $<
