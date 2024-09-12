#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc<2){
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int pipefd[2];
    if(pipe(pipefd)==-1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
     pid_t pid = fork();

     if(pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
     } else if(pid==0){
        struct timeval start;
        gettimeofday(&start, NULL);
        write(pipefd[1], &start, sizeof(start));
        close(pipefd[1]);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
     } else{
        int status;
        waitpid(pid, &status, 0);
        struct timeval start, end;
        read(pipefd[0], &start, sizeof(start));
        close(pipefd[0]);
        gettimeofday(&end, NULL);
        double elapsed = (end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000000.0;
        printf("Elapsed time (pipe): %.5f seconds\n", elapsed);
     }
     return 0;
}