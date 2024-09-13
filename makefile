CC = gcc
CFLAGS = -Wall
OBJS = common.o 

all: time time_shared time_pipe

common.o: common.c time.h
	$(CC) $(CFLAGS) -c common.c

time: time.c $(OBJS)
	$(CC) $(CFLAGS) -o time time.c $(OBJS)

time_shared: time_shared.c $(OBJS)
	$(CC) $(CFLAGS) -o time_shared time_shared.c $(OBJS)

time_pipe: time_pipe.c $(OBJS)
	$(CC) $(CFLAGS) -o time_pipe time_pipe.c $(OBJS)

clean:
	rm -f *.o time time_shared time_pipe

run: time time_shared time_pipe
	@echo "running simple..."
	./time ls
	@echo "running shared..."
	./time_shared ls
	@echo "running pipe..."
	./time_pipe ls

.PHONY: all clean run