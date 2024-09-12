#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc<2){
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid==0){
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&end, NULL);
        double total_time = (end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000000.0;
        printf("Elapsed time: %.5f seconds\n", total_time);
    }
    return 0;
}