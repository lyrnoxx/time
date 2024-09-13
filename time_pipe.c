#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);

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
        execute_command(argv);
     } else{
        int status;
        waitpid(pid, &status, 0);
        struct timeval start, end;
        read(pipefd[0], &start, sizeof(start));
        close(pipefd[0]);
        gettimeofday(&end, NULL);
        calculate_time(strat, end);
     }
     return 0;
}