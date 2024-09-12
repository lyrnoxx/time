CC = gcc
CFLAGS = -Wall

all: time time_shared time_pipe

time: time.c 
	$(CC) $(CFLAGS) -o time time.c 

time_shared: time_shared.c 
	$(CC) $(CFLAGS) -o time_shared time_shared.c

time_pipe: time_pipe.c 
	$(CC) $(CFLAGS) -o time_pipe time_pipe.c

clean:
	rm -f time time_shared time_pipe

depend: time.c time_shared.c time_pipe.c 
	$(CC) -MM time.c time_shared.c time_pipe.c > .depend

-include .depend

run: time time_shared time_pipe
	./time ls
	./time_shared ls
	./time_pipe ls

.PHONY: all clean depend run