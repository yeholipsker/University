/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex3
******************************************/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <memory.h>

#define SHM_SIZE 1024
#define ROW 8
#define BLACK 2
#define WHITE 1
#define EMPTY 0
void UsrHandle(int sig);
int SendPidFifo();
void AssignSignal();
char *PtrToShm();
void CreateBoard();
void PrintBoard();
int GetInputAndUpdate(int pInt[2]);
int InBorders(int x, int y);
void Board2Temp(int tempBoard[ROW][ROW]);
void Temp2Board(int tempBoard[ROW][ROW]);
int TempUpdate(int x, int y, int tempBoard[ROW][ROW]);
int UpdateRowRight(int x,int y,int tempBoard[ROW][ROW]);
int UpdateRowUp(int x,int y,int tempBoard[ROW][ROW]);
int UpdateRowDown(int x,int y,int tempBoard[ROW][ROW]);
int UpdateRowLeft(int x,int y,int tempBoard[ROW][ROW]);
int UpdateUpRight(int x,int y,int tempBoard[ROW][ROW]);
int UpdateDownRight(int x,int y,int tempBoard[ROW][ROW]);
int UpdateDownLeft(int x,int y,int tempBoard[ROW][ROW]);
int UpdateUpLeft(int x,int y,int tempBoard[ROW][ROW]);
void RotateTempRight(int tempBoard[ROW][ROW]);
void RotateXYRight(int * x, int * y);
int IsThereValid();
int CheckWinner();

int board[ROW][ROW];
int myColor, opponentColor;
char * shstr;

/************************************************************************
 * Function name: main
 * The input: no input
 * The output: 0 - exit code
 * The function operation: client for the reversi game.
*************************************************************************/
int main() {
    //variable declaration
    char c, op;
    int x, y, done, fifoFd;
    char buffer[4];
    int buffer2[2], myTurn = 0;
    int tempBoard[ROW][ROW];
    int temp;

    //send my pid by fifo
    fifoFd = SendPidFifo();

    //assign signal handler for SIGUSR1
    AssignSignal();

    //wait for SIGUSR1 signal from server
    pause();

    //get pointer to shared memory
    shstr = PtrToShm();

    //determine my color
    if (*shstr == 'b'){
        myColor = WHITE;
    } else {
        myColor = BLACK;
        myTurn = 1;
        //*shstr = 'b';
    }

    //get opponent's color
    if (myColor == BLACK){
        opponentColor = WHITE;
    } else {
        opponentColor = BLACK;
    }
    //create the board
    CreateBoard();

    do{
        if (myTurn){
            //get input from user
            done  = GetInputAndUpdate(buffer2);
            if (done){
                break;
            }
            //print the board
            PrintBoard();
            if (myColor == BLACK){
                c = 'b';
                op = 'w';
            } else {
                c = 'w';
                op = 'b';
            }
            sprintf(buffer,"%c%d%d\0",c,buffer2[0],buffer2[1]);
            strcpy(shstr,buffer);
            myTurn = 0;
        } else {
            while (*shstr == c){
                printf("Waiting for the other player to make a move\n");
                sleep(1);
            }
            //get the opponent move
            x = *(shstr+1) - '0';
            y = *(shstr+2) - '0';
            temp = opponentColor;
            opponentColor = myColor;
            myColor = temp;
            Board2Temp(tempBoard);
            TempUpdate(x, y, tempBoard);
            Temp2Board(tempBoard);
            PrintBoard();
            temp = opponentColor;
            opponentColor = myColor;
            myColor = temp;
            myTurn = 1;
        }
    }while (*shstr == 'b' || *shstr == 'w');

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

    //close fifo
    if(close(fifoFd) == -1){
        perror("failed to close");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/************************************************************************
 * Function name: GetInputAndUpdate
 * The input: no input
 * The output: no output
 * The function operation: gets user input and update board.
*************************************************************************/
int GetInputAndUpdate(int pInt[2]) {
    //variable declaration
    int x, y, inBorders, flip = 0, winner;
    int tempBoard[ROW][ROW];

    //check if there is valid moves
    if (!IsThereValid()){
        //if not - end game
        winner = CheckWinner();
        switch (winner){
            case 0:
                *shstr = '0';
                break;
            case 1:
                *shstr = '1';
                break;
            case 2:
                *shstr = '2';
                break;
        }
        return 1;
    } else {
        printf("Please choose a square\n");
        do{
            inBorders = 0;
            flip = 0;
            Board2Temp(tempBoard);
            scanf(" [%d,%d]", &x, &y);
            inBorders = InBorders(x, y);
            if(!inBorders){
                printf("No such square\n");
                printf("Please choose another square\n");
            } else {
                //else, try to update temp board
                flip = TempUpdate(x, y, tempBoard);
                //if nothing changed - illegal place
                if(!flip){
                    printf("This square is invalid\n");
                    printf("Please choose another square\n");
                }
            }
        }while (!flip || !inBorders);
    }
    pInt[0] = x;
    pInt[1] = y;
    //update the board
    Temp2Board(tempBoard);
    return 0;
}

/************************************************************************
 * Function name: CheckWinner
 * The input: no input
 * The output: winner num
 * The function operation: check who is the winner.
*************************************************************************/
int CheckWinner() {
    //variable declaration
    int i, j, numOf1 = 0, numOf2 = 0, ret = 0;
    //count the number of 1's and 2's
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            switch (board[i][j]){
                case 0:
                    break;
                case 1:
                    numOf1++;
                    break;
                case 2:
                    numOf2++;
                    break;
            }
        }
    }
    //report the winner
    if (numOf1 == numOf2){
        ret = 0;
    }
    if (numOf1 > numOf2){
        ret = 1;
    }
    if (numOf1 < numOf2){
        ret = 2;
    }
    return ret;
}

/************************************************************************
 * Function name: Temp2Board
 * The input: temp board
 * The output: no output
 * The function operation: copy temp board to board.
*************************************************************************/
void Temp2Board(int tempBoard[ROW][ROW]){
    int i,j;
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            board[i][j] = tempBoard[i][j];
        }
    }
}

/************************************************************************
 * Function name: IsThereValid
 * The input: no input
 * The output: 1 for true 0 for false
 * The function operation: check if there is valid place to play.
*************************************************************************/
int IsThereValid() {
    int i, j, flip = 0;
    int tempBoard[ROW][ROW];
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            if (board[i][j] == EMPTY){
                Board2Temp(tempBoard);
                flip += TempUpdate(j,i,tempBoard);
            }
        }
    }
    return flip;
}

/************************************************************************
 * Function name: TempUpdate
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the temp board and check if it has
 * influence on the tiles.
*************************************************************************/
int TempUpdate(int x, int y, int tempBoard[ROW][ROW]) {
    //variable declaration
    int flip = 0;

    //check if square is available
    if (board[y][x] != EMPTY){
        return flip;
    }

    //update y,x place with your color
    tempBoard[y][x] = myColor;

    //update to the right
    if ((x + 1) < ROW && tempBoard[y][x + 1] == opponentColor){
        flip += UpdateRowRight(x , y , tempBoard);
    }

    //update to up
    if ((y - 1) >= 0 && tempBoard[y - 1][x] == opponentColor){
        flip += UpdateRowUp(x , y , tempBoard);
    }

    //update to down
    if ((y + 1) < ROW && tempBoard[y + 1][x] == opponentColor){
        flip += UpdateRowDown(x , y , tempBoard);
    }

    //update to the left
    if ((x - 1) >= 0 && tempBoard[y][x - 1] == opponentColor){
        flip += UpdateRowLeft(x , y , tempBoard);
    }

    //update diagonally right and up
    if ((x + 1) < ROW && (y - 1) >= 0 &&
            tempBoard[y - 1][x + 1] == opponentColor){
        flip += UpdateUpRight(x , y , tempBoard);
    }

    //update diagonally right and down
    if ((x + 1) < ROW && (y + 1) < ROW &&
        tempBoard[y + 1][x + 1] == opponentColor){
        flip += UpdateDownRight(x , y , tempBoard);
    }

    //update diagonally left and down
    if ((x - 1) >= 0 && (y + 1) < ROW &&
        tempBoard[y + 1][x - 1] == opponentColor){
        flip += UpdateDownLeft(x , y , tempBoard);
    }

    //update diagonally left and up
    if ((x - 1) >= 0 && (y - 1) >= 0 &&
        tempBoard[y - 1][x - 1] == opponentColor){
        flip += UpdateUpLeft(x , y , tempBoard);
    }
    return flip;
}

/************************************************************************
 * Function name: UpdateUpLeft
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row diagonally up and left and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateUpLeft(int x,int y,int tempBoard[ROW][ROW]){
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateUpRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: UpdateDownLeft
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row diagonally down and left and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateDownLeft(int x,int y,int tempBoard[ROW][ROW]){
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateUpRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: UpdateDownRight
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row diagonally down and right and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateDownRight(int x,int y,int tempBoard[ROW][ROW]){
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateUpRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}
/************************************************************************
 * Function name: UpdateUpRight
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row diagonally up and right and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateUpRight(int x,int y,int tempBoard[ROW][ROW]) {
    //variable declaration
    int flip = 0, tempI = 8, tempJ = 0, i, j;
    for (i = y - 1, j = x + 1; i >= 0 && j < ROW; --i, ++j) {
        if (tempBoard[i][j] == EMPTY){
            return flip;
        }
        if (tempBoard[i][j] == myColor){
            flip = 1;
            tempI = i;
            tempJ = j;
            break;
        }
    }

    for (i = y - 1, j = x + 1; i > tempI && j < tempJ; --i, ++j){
        tempBoard[i][j] = myColor;
    }
    return flip;
}

/************************************************************************
 * Function name: UpdateRowLeft
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row to the down and check if it
 * has influence on the tiles.
*************************************************************************/
int UpdateRowLeft(int x,int y,int tempBoard[ROW][ROW]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateRowRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: UpdateRowDown
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row to the down and check if it
 * has influence on the tiles.
*************************************************************************/
int UpdateRowDown(int x,int y,int tempBoard[ROW][ROW]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateRowRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: UpdateRowUp
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row to the up and check if it
 * has influence on the tiles.
*************************************************************************/
int UpdateRowUp(int x,int y,int tempBoard[ROW][ROW]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = UpdateRowRight(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: RotateXYRight
 * The input: pointer to x, y indicates square
 * The output: no output
 * The function operation: rotates the x,y to the right (with the board).
*************************************************************************/
void RotateXYRight(int * x, int * y){
    int tempY;
    tempY = *y;
    *y = *x;
    *x = (7 - tempY);
}

/************************************************************************
 * Function name: RotateTempRight
 * The input: pointer to tempBoard
 * The output: no output
 * The function operation: rotates the tempBoard to the right.
*************************************************************************/
void RotateTempRight(int tempBoard[ROW][ROW]) {
    int i, j, temp[ROW][ROW];
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            temp[j][7 - i] = tempBoard[i][j];
        }
    }
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            tempBoard[i][j] = temp[i][j];
        }
    }
}

/************************************************************************
 * Function name: UpdateRowRight
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the row to the right and check if it
 * has influence on the tiles.
*************************************************************************/
int UpdateRowRight(int x,int y,int tempBoard[ROW][ROW]) {
    //variable declaration
    int flip = 0, temp = 0, i;

    for (i = x + 1; i < ROW; ++i) {
        if (tempBoard[y][i] == EMPTY){
            return flip;
        }
        if (tempBoard[y][i] == myColor){
            flip = 1;
            temp = i;
            break;
        }
    }
    for (i = x + 1; i < temp; ++i) {
        tempBoard[y][i] = myColor;
    }
    return flip;
}

/************************************************************************
 * Function name: Board2Temp
 * The input: pointer to tempBoard
 * The output: no output
 * The function operation: copy board to temp board.
*************************************************************************/
void Board2Temp(int tempBoard[ROW][ROW]) {
    int i,j;
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }
}

/************************************************************************
 * Function name: InBorders
 * The input: x,y indicates square
 * The output: 1 - true, 0 - false
 * The function operation: check if the square is in borders.
*************************************************************************/
int InBorders(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0){
        return 0;
    }
    return 1;
}

/************************************************************************
 * Function name: PrintBoard
 * The input: no input
 * The output: no output
 * The function operation: prints the board.
*************************************************************************/
void PrintBoard() {
    //variable declaration
    int i, j;
    printf("The board is:\n");
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
}

/************************************************************************
 * Function name: CreateBoard
 * The input: no input
 * The output: no output
 * The function operation: create and initialize board.
*************************************************************************/
void CreateBoard() {
    //variable declaration
    int i,j;
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < ROW; ++j) {
            board[i][j] = EMPTY;
        }
    }
    board[3][3] = board[4][4] = BLACK;
    board[3][4] = board[4][3] = WHITE;
}

/************************************************************************
 * Function name: PtrToShm
 * The input: no input
 * The output: pointer to shared memory
 * The function operation: get pointer to shared memory.
*************************************************************************/
char *PtrToShm() {
    //variable declaration
    int shmid;
    key_t key;
    char * shstr;

    //get the key for the shared memory
    if ((key = ftok("ex31.c", 'k')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //get the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0)) == -1) {
        perror("shmget");
        exit(1);
    }

    //get pointer to shared memory
    shstr = (char *)shmat(shmid,0,0666);
    if (shstr == (char *)(-1)) {
        perror("failed to shmat");
        exit(EXIT_FAILURE);
    }
    return shstr;
}

/************************************************************************
 * Function name: AssignSignal
 * The input: no input
 * The output: no output
 * The function operation: assign signal handler for SIGUSR1.
*************************************************************************/
void AssignSignal() {
    //variable declaration
    struct sigaction sigact;
    sigset_t sigset;

    //block all the signals
    sigfillset(&sigset);
    sigact.sa_mask = sigset;
    sigact.sa_flags = 0;

    //assign UsrHandle to be the handler to SIGUSR1
    sigact.sa_handler = UsrHandle;
    if (sigaction(SIGUSR1,&sigact,NULL) == -1){
        perror("failed to sigaction");
        exit(EXIT_FAILURE);
    }
}

/************************************************************************
 * Function name: SendPidFifo
 * The input: no input
 * The output: no output
 * The function operation: send my pid by fifo.
*************************************************************************/
int SendPidFifo() {
    //variable declaration
    int fifoFd, myPid;

    //open fifo
    fifoFd = open("fifo_clientTOserver",O_WRONLY);
    if(fifoFd == -1){
        perror("failed to open");
        exit(EXIT_FAILURE);
    }

    //write pid to fifo
    myPid = getpid();
    if (write(fifoFd,&myPid,sizeof(int)) == -1){
        perror("failed to write");
        exit(EXIT_FAILURE);
    }

    return fifoFd;
}

/************************************************************************
 * Function name: UsrHandle
 * The input: no input
 * The output: no output
 * The function operation: handle SIGUSR1.
*************************************************************************/
void UsrHandle(int sig){

}