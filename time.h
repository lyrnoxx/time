#ifndef time_h
#define time_h

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void check_usage(int argc);
void execute_command(char *argv[]);
void calculate_time(struct timeval start, struct timeval end);

#endif