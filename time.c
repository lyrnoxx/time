#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);
    struct timeval start, end;
    gettimeofday(&start, NULL);//set start time, done by parent

    pid_t pid = fork();
    if (pid<0){
        perror("fork");
        exit(1);
    } else if(pid==0){//child process has pid 0
        execute_command(argv);
    } else {//parent process
        int status;
        waitpid(pid, &status, 0);//waiting for child to complete
        gettimeofday(&end, NULL);//end time set by parent
        calculate_time(start, end);
    }
    return 0;
}