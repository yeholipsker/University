/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex2
******************************************/

#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_SIZE 80
#define ARR_SIZE 16
#define ROW_SIZE 4

void UsrHandle(int sig);
void IntHandle(int sig);
void ClearScreen();

/************************************************************************
 * Function name: main
 * The input: no input
 * The output: 0 - exit code
 * The function operation: handles the signals SIGINT, SIGUSR1.
*************************************************************************/
int main() {
    //variable declaration
    struct sigaction sigactUsr, sigactInt;
    sigset_t sigset;
    int true = 1;

    //block all the signals
    sigfillset(&sigset);
    sigdelset(&sigset, SIGINT);
    sigactUsr.sa_mask = sigset;
    sigactUsr.sa_flags = 0;

    //assign UsrHandle to be the handler to SIGUSR1
    sigactUsr.sa_handler = UsrHandle;
    if (sigaction(SIGUSR1,&sigactUsr,NULL) == -1){
        perror("failed to sigaction");
        exit(EXIT_FAILURE);
    }

    //assign IntHandle to be the handler to SIGINT
    sigactInt.sa_handler = IntHandle;
    if (sigaction(SIGINT,&sigactInt,NULL) == -1){
        perror("failed to sigaction");
        exit(EXIT_FAILURE);
    }
    while (true){}
    return 0;
}

/************************************************************************
 * Function name: UsrHandle
 * The input: signal number
 * The output: no output
 * The function operation: prints the board in graphic form.
*************************************************************************/
void UsrHandle(int sig) {
    // variable declaration
    char buffer[MAX_SIZE];
    char lbuffer[5];
    char bufferOut[1024];
    char * splitted[ARR_SIZE];
    char delim[3] = ",\n\0";
    memset(buffer,0,MAX_SIZE);
    memset(bufferOut,0,1024);
    memset(lbuffer,0,5);
    int i, j;

    //read from stdin
    if (read(STDIN_FILENO,buffer,MAX_SIZE) < 0){
        perror("failed to read from stdin");
        exit(EXIT_FAILURE);
    }

    //split the numbers
    splitted[0] = strtok(buffer,delim);
    for (i = 1; i < ARR_SIZE; ++i) {
        splitted[i] = strtok(NULL,delim);
    }

    ClearScreen();
    //loop over the array and print the board
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            strcat(bufferOut,"| ");
            if (atoi(splitted[ROW_SIZE * i + j])){
                sprintf(lbuffer, "%04d ", atoi(splitted[ROW_SIZE * i + j]));
                strcat(bufferOut,lbuffer);
            } else {
                strcat(bufferOut,"     ");
            }
        }
        strcat(bufferOut,"|\n");
    }
    if(write(STDOUT_FILENO,bufferOut,strlen(bufferOut)) == -1){
        perror("failed to write - board graphic");
        exit(EXIT_FAILURE);
    }
    //if there is 2048 - Win!
    if (strstr(bufferOut,"2048") != NULL){
        if(write(STDOUT_FILENO,"Congratulations!",16) == -1){
            perror("failed to write - Congratulations");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    //if the board is full - lose!
    if (strstr(bufferOut,"|      |") == NULL){
        if(write(STDOUT_FILENO,"Game Over!",10) == -1){
            perror("failed to write - Game Over");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}

/************************************************************************
 * Function name: IntHandle
 * The input: signal number
 * The output: no output
 * The function operation: prints BYE BYE and ends the process.
*************************************************************************/
void IntHandle(int sig) {
    if (write(STDOUT_FILENO,"BYE BYE",7) == -1){
        perror("failed to write - BYE BYE");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

/************************************************************************
*function name: ClearScreen*
*The Input: None*
*The output: None*
*The Function operation: clear the screen*
*************************************************************************/
void ClearScreen()
{
    // credit to Niv Beer who helped me with this function
    static int called = 0;
    char buffer[] = "\033[4A";
    if (!called)
    {
        called = 1;
        return;
    }
    if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){
        perror("failed to write - clear screen");
        exit(EXIT_FAILURE);
    }
}