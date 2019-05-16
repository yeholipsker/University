/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex3
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define SHM_SIZE 1024

/************************************************************************
 * Function name: main
 * The input: no input
 * The output: 0 - exit code
 * The function operation: server for the reversi game.
*************************************************************************/
int main() {
    //variable declaration
    key_t key;
    int shmid, fifoFd, pid1, pid2;
    char * shstr;

    //create the key
    if ((key = ftok("ex31.c", 'k')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //create the shared segment
    if ((shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
        perror("failed to shmget");
        exit(EXIT_FAILURE);
    }

    //get pointer to shared memory
    shstr = (char *)shmat(shmid,0,0666);
    if (shstr == (char *)(-1)) {
        perror("failed to shmat");
        exit(EXIT_FAILURE);
    }

    //iniztialize shared memory
    *shstr = 0;

    //create fifo
    if(mkfifo("fifo_clientTOserver",0666) == -1){
        perror("failed to mkfifo");
        exit(EXIT_FAILURE);
    }

    //open the fifo with read only permissions for waiting to clients
    fifoFd = open("fifo_clientTOserver",O_RDONLY);
    if(fifoFd == -1){
        perror("failed to open - 1");
        exit(EXIT_FAILURE);
    }

    //read from fifo pid
    if(read(fifoFd, &pid1, sizeof(int)) == -1){
        perror("failed to read");
        exit(EXIT_FAILURE);
    }

    //read from fifo pid
    if(read(fifoFd, &pid2, sizeof(int)) == -1){
        perror("failed to read");
        exit(EXIT_FAILURE);
    }

    //delete the fifo
    if(unlink("fifo_clientTOserver") == -1){
        perror("failed to close");
        exit(EXIT_FAILURE);
    }

    //signal to the first client to make his move
    if(kill(pid1,SIGUSR1) == -1){
        perror("failed to kill");
        exit(EXIT_FAILURE);
    }

    //wait for the client to write to shared memory
    while (*shstr != 'b'){
        sleep(1);
    }
    
    //signal to the second client to make his move
    if(kill(pid2,SIGUSR1) == -1){
        perror("failed to kill");
        exit(EXIT_FAILURE);
    }

    while (*shstr == 'w' || *shstr == 'b'){
        sleep(1);
    }

    //aprropriate messages for the end of the game
    printf("GAME OVER\n");
    if (*shstr == '1'){
        printf("Winning player: White\n");
    }
    if (*shstr == '2'){
        printf("Winning player: Black\n");
    }
    if (*shstr == '0'){
        printf("No winning player\n");
    }

    // detach from the segment
    if (shmdt(shstr) == -1) {
        perror("failed to shmdt");
        exit(EXIT_FAILURE);
    }

    //delete shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("failed to shmctl");
        exit(EXIT_FAILURE);
    }

    //close fifo
    if(close(fifoFd) == -1){
        perror("failed to close");
        exit(EXIT_FAILURE);
    }
    return 0;
}