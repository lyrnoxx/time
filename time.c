#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if (pid<0){
        perror("fork");
        exit(1);
    } else if(pid==0){
        execute_command(argv);
    } else {
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&end, NULL);
        calculate_time(start, end);
    }
    return 0;
}