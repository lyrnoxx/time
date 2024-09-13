#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);

   //setting up the pipe
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
        gettimeofday(&start, NULL);//child sets time, writes to the pipe and then closes the pipe
        write(pipefd[1], &start, sizeof(start));
        close(pipefd[1]);
        execute_command(argv);
     } else{
        int status;
        waitpid(pid, &status, 0);//waiting for child
        struct timeval start, end;
        read(pipefd[0], &start, sizeof(start));
        close(pipefd[0]);//parent reads the start time from the pipe and then closed the pipe
        gettimeofday(&end, NULL);//sets the end time
        calculate_time(start, end);
     }
     return 0;
}