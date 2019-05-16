/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex2
******************************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void AlrmHandle(int sig);
int pid1, pid2;

/************************************************************************
 * Function name: main
 * The input: process id
 * The output: 0 - exit code
 * The function operation: restart the board, handles user keys.
*************************************************************************/
int main(int argc, char * argv[]) {
    //variable declaration
    int time, status;
    char buffer[20];
    struct sigaction sigact;
    sigset_t sigset;
    int fd[2];

    //block all the signals
    sigfillset(&sigset);
    sigdelset(&sigset, SIGINT);
    sigact.sa_mask = sigset;
    sigact.sa_flags = 0;

    //assign AlrmHandle to be the handler to SIGALRM
    sigact.sa_handler = AlrmHandle;
    if (sigaction(SIGALRM,&sigact,NULL) == -1){
        perror("failed to sigaction");
        exit(EXIT_FAILURE);
    }

    time = atoi(argv[1]);

    //initialize pipe
    if (pipe(fd) == -1) {
        perror("failed to pipe");
        exit(EXIT_FAILURE);
    }

    //run process 1
    if ((pid1 = fork()) == -1){
        perror("failed to fork - 1");
        exit(EXIT_FAILURE);
    }
    if(pid1 == 0) {
        if(dup2(fd[0],STDIN_FILENO) == -1){
            perror("dup process1 failed");
            exit(EXIT_FAILURE);
        }
        if (close(fd[0]) == -1 || close(fd[1]) == -1) {
            perror("close of fd failed");
            exit(EXIT_FAILURE);
        }
        execlp("./ex2_inp.out", "ex2_inp.out", NULL);
    }

    //run process 2
    if ((pid2 = fork()) == -1){
        perror("failed to fork - 2");
        exit(EXIT_FAILURE);
    }
    if(pid2 == 0) {
        if(dup2(fd[1],STDOUT_FILENO) == -1){
            perror("dup process2 failed");
            exit(EXIT_FAILURE);
        }
        if (close(fd[0]) == -1 || close(fd[1]) == -1) {
            perror("close of fd failed");
            exit(EXIT_FAILURE);
        }
        sprintf(buffer,"%d",pid1);
        sleep(1);
        execlp("./ex2_upd.out", "ex2_upd.out", buffer, NULL);
    }

    if (close(fd[0]) == -1 || close(fd[1]) == -1) {
        perror("close of fd failed");
        exit(EXIT_FAILURE);
    }
    //call alarm when time ends
    alarm(time);

    //wait for the processes to end
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);

    return 0;
}

/************************************************************************
 * Function name: AlrmHandle
 * The input: signal number
 * The output: no output
 * The function operation: handle SIGALRM signal.
*************************************************************************/
void AlrmHandle(int sig){
    //send SIGINT to the processes
    if(kill(pid2, SIGINT) == -1){
        perror("failed to signal 2");
        exit(EXIT_FAILURE);
    }
    if(kill(pid1, SIGINT) == -1){
        perror("failed to signal 1");
        exit(EXIT_FAILURE);
    }
}