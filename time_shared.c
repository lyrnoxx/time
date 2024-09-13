#include <sys/shm.h>
#include <sys/ipc.h>
#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);
    
    //creating shared memory
    int shm_id = shmget(IPC_PRIVATE, sizeof(struct timeval), IPC_CREAT | 0666);
    if(shm_id<0){
        perror("shmget failure");
        exit(1);
    }
    struct timeval *start = (struct timeval *)shmat(shm_id, NULL, 0);

    pid_t pid = fork();
    if (pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid==0){//child process sets the start time and then execute
        gettimeofday(start, NULL);
        execute_command(argv);
    } else {
        int status;
        waitpid(pid, &status, 0);
        struct timeval end;
        gettimeofday(&end, NULL);//after waiting for the child to complete, sets end time
        calculate_time(*start, end);
        shmdt(start);//removing the shared memory
        shmctl(shm_id, IPC_RMID, NULL);
    }
    return 0;
}