#include "time.h"

void check_usage(int argc){
    if(argc<2){
        fprintf(stderr, "Usage: filename(exe) <command> [args...]\n");
        exit(EXIT_FAILURE);
    }
}

void execute_command(char *argv[]){
    execvp(argv[1], &argv[1]);
    perror("execvp failed");
    exit(1)
}

void calculate_time(struct timeval start, struct timeval end){
    double total_time = (end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000000.0;
    printf("Elapsed time: %.5f seconds\n", total_time);
}