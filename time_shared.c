#include <sys/shm.h>
#include <sys/ipc.h>
#include "time.h"

int main(int argc, char *argv[]){
    check_usage(argc);
    
    int shm_id = shmget(IPC_PRIVATE, sizeof(struct timeval), IPC_CREAT | 0666);
    if(shm_id<0){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    struct timeval *start = (struct timeval *)shmat(shm_id, NULL, 0);

    pid_t pid = fork();
    if (pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid==0){
        gettimeofday(start, NULL);
        execute_command(argv);
    } else {
        int status;
        waitpid(pid, &status, 0);
        struct timeval end;
        gettimeofday(&end, NULL);
        calculate_time(*start, end);
        shmdt(start);
        shmctl(shm_id, IPC_RMID, NULL);
    }
    return 0;
}