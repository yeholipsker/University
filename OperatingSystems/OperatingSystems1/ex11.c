/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex1
******************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define SIZE 1

/************************************************************************
 * Function name: main
 * The input: 2 paths of files
 * The output: 1 - identical files, 2 - simillar, 3 - different
 * The function operation: compares every character. skips white spaces.
*************************************************************************/
int main(int argc, char *argv[]) {
    //variable declaration
    int fd1, fd2, size1 = 1, size2 = 1, retVal = 1;
    char buffer1[SIZE], buffer2[SIZE];
    //initialize buffers
    buffer1[0] = 0;
    buffer2[0] = 0;
    //open first file
    fd1 = open(argv[1],O_RDONLY);
    if (fd1 < 0){
        perror("open file not succeeded");
        exit(-1);
    }
    //open second file
    fd2 = open(argv[2],O_RDONLY);
    if (fd2 < 0){
        perror("open file not succeeded");
        exit(-1);
    }
    //read every charuntil one of the files ends
    while (size1 == 1 && size2 == 1){
        //read to buffer 1
        size1 = read(fd1,buffer1,1);
        if (size1 < 0) {
            perror("failed to read from file");
            exit(-1);
        }
        //read to buffer 2
        size2 = read(fd2,buffer2,1);
        if (size2 < 0) {
            perror("failed to read from file");
            exit(-1);
        }
        //if the chars different
        if (buffer1[0] != buffer2[0]){
            //first change to simillar (cant be identical)
            retVal = 2;
            //skip spaces for first file
            while (isspace(buffer1[0]) && size1 == 1){
                size1 = read(fd1,buffer1,1);
                if (size1 < 0) {
                    perror("failed to read from file");
                    exit(-1);
                }
            }
            //skip spaces for second file
            while (isspace(buffer2[0]) && size2 == 1){
                size2 = read(fd2,buffer2,1);
                if (size2 < 0) {
                    perror("failed to read from file");
                    exit(-1);
                }
            }
            //check if the char is not similar break and return 3
            if (toupper(buffer1[0]) != toupper(buffer2[0])){
                retVal = 3;
                break;
            }
        }
    }
    //close fd's
    if (close(fd1) < 0) {
        perror("failed to close file");
        exit(-1);
    }
    if (close(fd2) < 0) {
        perror("failed to close file");
        exit(-1);
    }
    return retVal;
}