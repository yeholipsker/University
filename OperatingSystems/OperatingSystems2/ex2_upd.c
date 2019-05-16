/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex2
******************************************/

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>

#define ROW_SIZE 4
#define BUFFER_SIZE 5

void RestartBoard();
void WriteRandSignal();
void AlrmHandle(int sig);
int Is2048();
int BoardFull();
void MoveRight();
void MoveUp();
void RotateRight();
void MoveDown();
void MoveLeft();
void IntHandle(int sig);

char GetOption();

int pid;
int board[ROW_SIZE][ROW_SIZE];
int true = 1;

/************************************************************************
 * Function name: main
 * The input: process id
 * The output: 0 - exit code
 * The function operation: restart the board, handles user keys.
*************************************************************************/
int main(int argc, char * argv[]) {
    //variable declaration
    struct sigaction sigact;
    sigset_t sigset;
    char option;

    //get the pid from argument
    pid = atoi(argv[1]);

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

    //assign IntHandle to be the handler to SIGINT
    sigact.sa_handler = IntHandle;
    if (sigaction(SIGINT,&sigact,NULL) == -1){
        perror("failed to sigaction");
        exit(EXIT_FAILURE);
    }

    //restart the board
    RestartBoard();

    //write the board to stdout and signal
    WriteRandSignal();

    while (true){
        system("stty cbreak -echo");
        option = (char)getchar();
        system("stty cooked echo");
        switch (option){
            case 'A':
                MoveLeft();
                WriteRandSignal();
                break;
            case 'D':
                MoveRight();
                WriteRandSignal();
                break;
            case 'W':
                MoveUp();
                WriteRandSignal();
                break;
            case 'X':
                MoveDown();
                WriteRandSignal();
                break;
            case 'S':
                RestartBoard();
                WriteRandSignal();
                break;
            default:
                break;
        }
        //if there is 2048 in board or board is full - end game!
        if (Is2048() || BoardFull()){
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}

/************************************************************************
 * Function name: MoveLeft
 * The input: no input
 * The output: no output
 * The function operation: update the board to the Left.
*************************************************************************/
void MoveLeft() {
    RotateRight();
    RotateRight();
    MoveRight();
    RotateRight();
    RotateRight();
}

/************************************************************************
 * Function name: MoveDown
 * The input: no input
 * The output: no output
 * The function operation: update the board to the Down.
*************************************************************************/

void MoveDown() {
    RotateRight();
    RotateRight();
    RotateRight();
    MoveRight();
    RotateRight();
}

/************************************************************************
 * Function name: MoveUp
 * The input: no input
 * The output: no output
 * The function operation: update the board to the up.
*************************************************************************/
void MoveUp() {
    RotateRight();
    MoveRight();
    RotateRight();
    RotateRight();
    RotateRight();
}

/************************************************************************
 * Function name: RotateRight
 * The input: no input
 * The output: no output
 * The function operation: rotates the board to the right.
*************************************************************************/
void RotateRight() {

    int i, j, tempBoard[ROW_SIZE][ROW_SIZE];
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            tempBoard[j][3-i] = board[i][j];
        }
    }
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            board[i][j] = tempBoard[i][j];
        }
    }
}

/************************************************************************
 * Function name: MoveRight
 * The input: no input
 * The output: no output
 * The function operation: update the board to the right.
*************************************************************************/
void MoveRight() {
    //variable declaration
    int temp, i, j, k, l;
    for (k = 0; k < 4; ++k) {
        for (i = 4 - 1; i > 0; --i) {
            if (board[k][i] != 0){
                for (j = i - 1; j >= 0; --j) {
                    if (board[k][j] != 0){
                        if (board[k][i] == board[k][j]){
                            board[k][j] += board[k][i];
                            board[k][i] = 0;
                            i = j - 1;
                        }
                        break;
                    }
                }
            }
        }
    }
    for (l = 0; l < 4; ++l) {
        temp = 4-1;
        for (i = 4-1; i >= 0; --i) {
            if (board[l][i] != 0){
                if(i != temp){
                    board[l][temp] = board[l][i];
                    board[l][i] = 0;
                }
                temp--;
            }
        }
    }
}

/************************************************************************
 * Function name: RestartBoard
 * The input: no input
 * The output: no output
 * The function operation: restart the board.
*************************************************************************/
void RestartBoard() {
    //variable declaration
    int rand1i, rand1j, rand2i, rand2j, i, j;
    time_t t;

    srand((unsigned) time(&t));

    //set the board to zero
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    //determine randomly the places on board
    rand1i = rand() % ROW_SIZE;
    rand1j = rand() % ROW_SIZE;
    board[rand1i][rand1j] = 2;
    while (1){
        rand2i = rand() % ROW_SIZE;
        rand2j = rand() % ROW_SIZE;
        if (rand2i != rand1i || rand2j != rand1j){
            break;
        }
    }
    board[rand2i][rand2j] = 2;
}

/************************************************************************
 * Function name: WriteRandSignal
 * The input: no input
 * The output: no output
 * The function operation: write the board to stdout and signal to pid.
*************************************************************************/
void WriteRandSignal() {
    //variable declaration
    int randTime, i, j;
    char buffer[5];
    memset(buffer,0,BUFFER_SIZE);
    char bufferOut[80];
    memset(buffer,0,80);

    //write the board to stdout
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            if (i == ROW_SIZE - 1 && j == ROW_SIZE - 1){
                sprintf(buffer,"%d\n",board[i][j]);

            } else {
                sprintf(buffer,"%d,",board[i][j]);
            }
            strcat(bufferOut,buffer);
        }
    }
    if (write(STDOUT_FILENO,bufferOut,strlen(bufferOut)) == -1){
        perror("failed to write - board");
        exit(EXIT_FAILURE);
    }

    //signal to pid
    if(kill(pid, SIGUSR1) == -1){
        perror("failed to signal to output");
        exit(EXIT_FAILURE);
    }

    //if there is 2048 in board or board is full - end game!
    if (Is2048() || BoardFull()){
        kill(pid, SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    
    //assign random delay time
    randTime = (rand() % 5) + 1;

    //alarm after 'randTime' seconds
    alarm(randTime);
}

/************************************************************************
 * Function name: AlrmHandle
 * The input: signal number
 * The output: no output
 * The function operation: handle SIGALRM signal.
*************************************************************************/
void AlrmHandle(int sig){
    //variable declaration
    int newRandI,newRandJ;

    //put 2 in random place in board
    do{
        newRandI = rand() % ROW_SIZE;
        newRandJ = rand() % ROW_SIZE;
    }while (board[newRandI][newRandJ]);
    board[newRandI][newRandJ] = 2;

    //write the board to stdout and sidnal and new random time
    WriteRandSignal();
}

/************************************************************************
 * Function name: BoardFull
 * The input: no input
 * The output: 0 - false, 1 - true
 * The function operation: check if the board full
*************************************************************************/
int BoardFull() {
    int i, j;
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            if (board[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

/************************************************************************
 * Function name: Is2048
 * The input: no input
 * The output: 0 - false, 1 - true
 * The function operation: check if there 2048 in the board.
*************************************************************************/
int Is2048() {
    int i, j;
    for (i = 0; i < ROW_SIZE; ++i) {
        for (j = 0; j < ROW_SIZE; ++j) {
            if (board[i][j] == 2048){
                return 1;
            }
        }
    }
    return 0;
}

/************************************************************************
 * Function name: IntHandle
 * The input: signal number
 * The output: no output
 * The function operation: handle SIGINT signal.
*************************************************************************/
void IntHandle(int sig){
    exit(EXIT_SUCCESS);
}
