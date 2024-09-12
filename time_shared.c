#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char *argv[]){
    if(argc<2){
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
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
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        struct timeval end;
        gettimeofday(&end, NULL);
        double total_time = (end.tv_sec-start->tv_sec)+(end.tv_usec-start->tv_usec)/1000000.0;
        printf("Elapsed time (shared): %.5f seconds\n", total_time);
        shmdt(start);
        shmctl(shm_id, IPC_RMID, NULL);
    }
    return 0;
}