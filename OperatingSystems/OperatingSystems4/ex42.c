/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex4
******************************************/
#include <sys/time.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <memory.h>

#define SHM_SIZE 1024
#define BUF_SIZE 150

struct node
{
    char val;
    struct node * ptr;
};

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

void * func(void * arg);
void Enqueue(char option);
char Dequeue();
void Initialization();
int GetShMem(char **shm_ptr);
void SemCreate();
void ThreadPoolCreate();
void PrintToFile(unsigned long threadId);
void End(int i);

int internal_count = 0;
struct node *start = NULL;
struct node *end = NULL;
pthread_mutex_t lock;
int fd, flag = 1, thFlag = 1;
pthread_t threads[5];
union semun arg;
int semid;

/************************************************************************
 * Function name: main
 * The input: no input
 * The output: 0 - exit code
 * The function operation: server for user's input.
*************************************************************************/
int main(){

    //variable declaration
    int shm_id, i;
    char * shm_ptr = NULL, option;
    struct sembuf sb;

    //initialization
    Initialization();

    //get shared memory
    shm_id = GetShMem(&shm_ptr);

    //create semaphores
    SemCreate();

    ThreadPoolCreate();

    while (flag){
        //try reading shared memory
        sb.sem_flg = 0;
        sb.sem_num = 0;
        sb.sem_op = -1;
        if (semop(semid, &sb, 1) == -1) {
            perror("failed to semop lock");
            exit(EXIT_FAILURE);
        }
        //read from shared memory and put in jobs queue
        option = *shm_ptr;
        if (option == 'g') {
            //cancel all threads
            for (i = 0; i < 5; ++i) {
                pthread_cancel(threads[i]);
            }
            //print to file
            PrintToFile((unsigned long) pthread_self());
            break;
        }
        if (option == 'h'){
            //finish all jobs and threads
            thFlag = 0;
            for (i = 0; i < 5; ++i) {
                sb.sem_flg = 0;
                sb.sem_num = 2;
                sb.sem_op = 1;
                if (semop(semid, &sb, 1) == -1) {
                    perror("failed to semop lock");
                    exit(EXIT_FAILURE);
                }
            }
            for (i = 0; i < 5; ++i) {
                pthread_join(threads[i],NULL);
            }
            //print to file
            PrintToFile((unsigned long) pthread_self());
            break;
        }
        Enqueue(option);
        //add 1 to threads handler semaphore
        sb.sem_flg = 0;
        sb.sem_num = 2;
        sb.sem_op = 1;
        if (semop(semid, &sb, 1) == -1) {
            perror("failed to semop lock");
            exit(EXIT_FAILURE);
        }
        //unlock writing to shared memory
        sb.sem_flg = 0;
        sb.sem_num = 1;
        sb.sem_op = 1;
        if (semop(semid, &sb, 1) == -1) {
            perror("failed to semop lock");
            exit(EXIT_FAILURE);
        }
    }

    End(shm_id);
    return 0;
}

/************************************************************************
 * Function name: Initialization
 * The input: no input
 * The output: no output
 * The function operation: initialize rand, mutex and open file.
*************************************************************************/
void Initialization() {
    //variable declaration
    time_t t;

    //initiate random
    srand((unsigned) time(&t));

    //initiate mutex
    if(pthread_mutex_init(&lock,NULL) != 0){
        perror("failed to pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    //create <ID>.txt file
    fd = open("204038533.txt",O_TRUNC | O_CREAT | O_RDWR, 0666);
    if (fd == -1){
        perror("failed to open file");
        exit(EXIT_FAILURE);
    }
}

/************************************************************************
 * Function name: GetShMem
 * The input: pointer to pointer of shared memory
 * The output: shm_id
 * The function operation: grab shared memory.
*************************************************************************/
int GetShMem(char **shm_ptr) {
    //variable declaration
    key_t key;
    int shm_id;

    //get the key for shared memory
    if ((key = ftok("204038533.txt", 'Y')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //create shared memory
    if ((shm_id = shmget(key, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
        perror("failed to shmget");
        exit(EXIT_FAILURE);
    }

    //get the pointer to shared memory
    *shm_ptr = shmat(shm_id, NULL, 0);
    if (*shm_ptr == (char *)(-1)) {
        perror("failed to shmat");
        exit(EXIT_FAILURE);
    }

    return shm_id;
}

/************************************************************************
 * Function name: SemCreate
 * The input: no input
 * The output: no output
 * The function operation: initialize semaphores.
*************************************************************************/
void SemCreate() {
    //variable declaration
    key_t key;

    //get the key for semaphores
    if ((key = ftok("204038533.txt", 'L')) == -1) {
        perror("failed to ftok");
        exit(EXIT_FAILURE);
    }

    //get the semid
    semid = semget(key, 3, IPC_CREAT | 0666);
    if (semid == -1){
        perror("failed to semget");
        exit(EXIT_FAILURE);
    }

    //initialize 3 semaphores (reading, writing, threads)
    arg.array=(ushort*)malloc(3*sizeof(ushort));
    arg.array[0] = 0;
    arg.array[1] = 1;
    arg.array[2] = 0;
    if(semctl(semid,0,SETALL,arg) == -1){
        perror("failed to semctl");
        exit(EXIT_FAILURE);
    }
}

/************************************************************************
 * Function name: ThreadPoolCreate
 * The input: semaphore id
 * The output: no output
 * The function operation: creates threadpool.
*************************************************************************/
void ThreadPoolCreate() {
    //variable declaration
    int i, fail;

    // Create the threads
    for(i = 0; i < 5; i++) {
        fail = pthread_create(&threads[i], NULL, func, NULL);
        if (fail)
            printf("Create thread failed with error %d\n", fail);
    }
}

/************************************************************************
 * Function name: func
 * The input: pointer to arguments
 * The output: no output
 * The function operation: function for threads.
*************************************************************************/
void * func(void * arg){
    //variable declaration
    struct timespec req;
    int time, toAdd;
    char option;
    struct sembuf sb;
    //loop for threads
    while(thFlag) {
        //only threads inthe size of the jobs queue can get to this code
        sb.sem_flg = 0;
        sb.sem_num = 2;
        sb.sem_op = -1;
        if (semop(semid, &sb, 1) == -1) {
            perror("failed to semop lock");
            exit(EXIT_FAILURE);
        }
        if(pthread_mutex_lock(&lock) != 0){
            perror("failed to pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        //get job
        option = Dequeue();
        switch (option){
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
                //sleep for x nanoseconds
                time = rand() % 91 + 10;
                req.tv_sec = 0;
                req.tv_nsec = time;
                if (nanosleep(&req, NULL) == -1){
                    perror("failed to nanosleep");
                    exit(EXIT_FAILURE);
                }
                //add to internal_count
                toAdd = option - 'a' + 1;
                internal_count += toAdd;
                break;
            case 'f':
                //print to file
                PrintToFile((unsigned long)pthread_self());
                break;
            default:
                break;
        }
        if(pthread_mutex_unlock(&lock) != 0){
            perror("failed to pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }
    if(pthread_mutex_lock(&lock) != 0){
        perror("failed to pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
    //print before ending the thread
    PrintToFile((unsigned long)pthread_self());
    if(pthread_mutex_unlock(&lock) != 0){
        perror("failed to pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}

/************************************************************************
 * Function name: PrintToFile
 * The input: thread identifier
 * The output: no output
 * The function operation: prints to file.
*************************************************************************/
void PrintToFile(unsigned long threadId) {
    //variable declaration
    char buffer[BUF_SIZE];
    //write to file
    memset(buffer,0,BUF_SIZE);
    sprintf(buffer,"thread identifier is %lu and internal_count"
            " is %d\n", threadId , internal_count);
    if(write(fd,buffer,strlen(buffer)) == -1){
        perror("failed to write");
        exit(EXIT_FAILURE);
    }
}

/************************************************************************
 * Function name: End
 * The input: semaphore id, shared memory id
 * The output: no output
 * The function operation: free resources.
*************************************************************************/
void End(int shm_id) {
    //destroy mutex
    if(pthread_mutex_destroy(&lock) != 0){
        perror("failed to pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    //close file
    if(close(fd) == -1){
        perror("failed to close");
        exit(EXIT_FAILURE);
    }

    //remove semaphores
    if(semctl (semid, 0, IPC_RMID, arg) == -1){
        perror("failed to semctl");
        exit(EXIT_FAILURE);
    }
    //delete shared memory
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("failed to shmctl");
        exit(EXIT_FAILURE);
    }
    free(arg.array);
}

/************************************************************************
 * Function name: Enqueue
 * The input: data
 * The output: no output
 * The function operation: add data to queue.
*************************************************************************/
void Enqueue(char option) {
    //variable declaration
    struct node *temp;

    //allocate memory for new node
    temp = (struct node *)malloc(sizeof(struct node));
    temp->val = option;
    temp->ptr = NULL;

    //if queue is empty add the first element
    if (end  ==  NULL)
    {
        start = end = temp;
    }
        //else - add to the end of the queue
    else
    {
        end->ptr = temp;
        end = temp;
    }
}

/************************************************************************
 * Function name: Dequeue
 * The input: no input
 * The output: data
 * The function operation: delete data from queue, and pop it.
*************************************************************************/
char Dequeue() {
    //variable declaration
    struct node * temp;
    char tempChar;

    //temporary pointer to start fo queue
    temp = start;

    //if queue is empty
    if (start == NULL)
    {
        start = end = NULL;
        tempChar = 0;
    }
        //else - delete the node
    else
    {
        if (start == end){

        }
        tempChar = start->val;
        if (start == end){
            start = end = NULL;
        } else{
            start = start->ptr;
        }
        free(temp);
    }
    return tempChar;
}
