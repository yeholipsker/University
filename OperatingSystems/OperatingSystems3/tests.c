#include <stdio.h>

int board[8][8] = {{0, 0, 1, 1, 0, 0, 0, 0},
                   {1, 0, 2, 2, 1, 0, 0, 0},
                   {0, 0, 2, 2, 2, 1, 0, 0},
                   {2, 2, 0, 2, 2, 1, 0, 0},
                   {0, 2, 2, 2, 2, 0, 0, 0},
                   {1, 0, 2, 2, 2, 0, 0, 0},
                   {0, 2, 1, 0, 0, 2, 0, 0},
                   {0, 1, 0, 0, 0, 0, 1, 0}};
int myColor = 1;

void Board2Temp(int tempBoard[8][8]) {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }
}

void PrintBoard(int tempBoard[8][8]) {
    //variable declaration
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            printf("%d", tempBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/************************************************************************
 * Function name: UpdateUpLeft
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the 8 diagonally up and left and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateUpLeft(int x,int y,int tempBoard[8][8]){
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
 * The function operation: updates the 8 diagonally down and left and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateDownLeft(int x,int y,int tempBoard[8][8]){
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
 * The function operation: updates the 8 diagonally down and right and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateDownRight(int x,int y,int tempBoard[8][8]){
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
 * The function operation: updates the 8 diagonally up and right and
 * check if it has influence on the tiles.
*************************************************************************/
int UpdateUpRight(int x,int y,int tempBoard[8][8]) {
    //variable declaration
    int flip = 0, tempI = 0, tempJ, i, j;
    for (i = y - 1, j = x + 1; i >= 0, j < 8; --i, ++j) {
        if (tempBoard[i][j] == 0){
            return flip;
        }
        if (tempBoard[i][j] == myColor){
            flip = 1;
            tempI = i;
            tempJ = j;
            break;
        }
    }

    for (i = y - 1, j = x + 1; i > tempI, j < tempJ; --i, ++j){
        tempBoard[i][j] = myColor;
    }
    return flip;
}

/************************************************************************
 * Function name: Update8Left
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the 8 to the down and check if it
 * has influence on the tiles.
*************************************************************************/
int Update8Left(int x,int y,int tempBoard[8][8]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = Update8Right(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: Update8Down
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the 8 to the down and check if it
 * has influence on the tiles.
*************************************************************************/
int Update8Down(int x,int y,int tempBoard[8][8]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = Update8Right(x, y, tempBoard);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    return flip;
}

/************************************************************************
 * Function name: Update8Up
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the 8 to the up and check if it
 * has influence on the tiles.
*************************************************************************/
int Update8Up(int x,int y,int tempBoard[8][8]) {
    int flip;
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    RotateTempRight(tempBoard);
    RotateXYRight(&x, &y);
    flip = Update8Right(x, y, tempBoard);
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
void RotateTempRight(int tempBoard[8][8]) {
    int i, j, temp[8][8];
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            temp[j][7 - i] = tempBoard[i][j];
        }
    }
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            tempBoard[i][j] = temp[i][j];
        }
    }
}

/************************************************************************
 * Function name: Update8Right
 * The input: x, y indicates square ,pointer to tempBoard
 * The output: 1 - there was a flip, 0 - there wasn't
 * The function operation: updates the 8 to the right and check if it
 * has influence on the tiles.
*************************************************************************/
int Update8Right(int x,int y,int tempBoard[8][8]) {
    //variable declaration
    int flip = 0, temp = 0, i;

    for (i = x + 1; i < 8; ++i) {
        if (tempBoard[y][i] == 0){
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

int main(){
    int tempBoard[8][8];
    int flip = 0;
    Board2Temp(tempBoard);
    int x = 2, y = 3;
    board;
    tempBoard[y][x] = myColor;
    PrintBoard(tempBoard);
    //update y,x place with your color
    tempBoard[y][x] = myColor;

    //update to the right
    if ((x + 1) < 8 && tempBoard[y][x + 1] == 2){
        flip += Update8Right(x , y , tempBoard);
    }

    //update to up
    if ((y + 1) < 8 && tempBoard[y + 1][x] == 2){
        flip += Update8Up(x , y , tempBoard);
    }

    //update to down
    if ((y - 1) > 0 && tempBoard[y - 1][x] == 2){
        flip += Update8Down(x , y , tempBoard);
    }

    //update to the left
    if ((x - 1) > 0 && tempBoard[y][x - 1] == 2){
        flip += Update8Left(x , y , tempBoard);
    }

    //update diagonally right and up
    if ((x + 1) < 8 && (y - 1) > 0 &&
        tempBoard[y - 1][x + 1] == 2){
        flip += UpdateUpRight(x , y , tempBoard);
    }

    //update diagonally right and down
    if ((x + 1) < 8 && (y + 1) > 0 &&
        tempBoard[y + 1][x + 1] == 2){
        flip += UpdateDownRight(x , y , tempBoard);
    }

    //update diagonally left and down
    if ((x - 1) < 8 && (y + 1) > 0 &&
        tempBoard[y + 1][x - 1] == 2){
        flip += UpdateDownLeft(x , y , tempBoard);
    }

    //update diagonally left and up
    if ((x - 1) < 8 && (y - 1) > 0 &&
        tempBoard[y - 1][x - 1] == 2){
        flip += UpdateUpLeft(x , y , tempBoard);
    }
    //flip = UpdateUpRight(x,y,tempBoard);
    PrintBoard(tempBoard);
    printf("%d\n", flip);
    return 0;
}
