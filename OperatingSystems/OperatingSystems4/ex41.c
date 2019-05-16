/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex4
******************************************/
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define SHM_SIZE 1024

/************************************************************************
 * Function name: main
 * The input: no input
 * The output: 0 - exit code
 * The function operation: client side.
*************************************************************************/
int main(){

    //variables declaration
    key_t key, key1;
    int shm_id, semid;
    char * shm_ptr;
    char input = 0;
    struct sembuf sb;

    //get the key for shared memory
    if ((key = ftok("204038533.txt", 'Y')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //get the key for semaphores
    if ((key1 = ftok("204038533.txt", 'L')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //grab the shared memory created by server
    if ((shm_id = shmget(key, SHM_SIZE, 0)) == -1) {
        perror("failed to shmget");
        exit(EXIT_FAILURE);
    }

    //get the pointer to shared memory
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("failed to shmat");
        exit(EXIT_FAILURE);
    }

    //get semid
    semid = semget(key1, 2, 0);
    if (semid == -1){
        perror("failed to semget");
        exit(EXIT_FAILURE);
    }
    sb.sem_flg = 0;

    //loop for user's input
    while (input != 'i'){
        //get user's input
        printf("Please enter request code\n");
        scanf(" %c", &input);
        //convert to lowercase for supporting upper and lower case
        input = (char)tolower(input);
        //try writing shared memory
        sb.sem_num = 1;
        sb.sem_op = -1;
        if (semop(semid, &sb, 1) == -1) {
            //if server closed
            if (errno == EINVAL || errno == EIDRM){
                // detach from the segment
                if (shmdt(shm_ptr) == -1) {
                    perror("failed to shmdt");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
            perror("failed to semop");
            exit(EXIT_FAILURE);
        }
        //write ueser's input to shared memory
        *shm_ptr = input;
        //unlock reading to shared memory
        sb.sem_num = 0;
        sb.sem_op = 1;
        if (semop(semid, &sb, 1) == -1) {
            //if server closed
            if (errno == EINVAL || errno == EIDRM){
                // detach from the segment
                if (shmdt(shm_ptr) == -1) {
                    perror("failed to shmdt");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
            perror("failed to semop");
            exit(EXIT_FAILURE);
        }
        //if user's input equals i clean resources and end loop
        if (input == 'i'){
            // detach from the segment
            if (shmdt(shm_ptr) == -1) {
                perror("failed to shmdt");
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}
