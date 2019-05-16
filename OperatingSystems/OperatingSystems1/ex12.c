/******************************************
 * Student name: Yehoshua Lipsker
 * Student ID:  204038533
 * Course Exercise Group:89-231-06
 * Exercise name: Ex1
******************************************/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define CONF_SIZE 480
#define PATH_SIZE 160
#define GRADE_SIZE 4

//function declaration
void PathCreator(char *buffer, char *path, char *dir);

void FindCFile(char *cFilePath, char *dirPath, int *depth);

int IsCFile(char *name);

int IsLegalDir(char *path, char *name);

void WriteLine(char *result, char *name, char *grade, char *info, int fd);

void Compile(char *path);

void Run(char *inPath, char *cFilePath);

void RunComp(char *path, char *outPath);

int CalcGrade(char *path, int *depth);

/************************************************************************
 * Function name: main
 * The input: path for configuration file
 * The output: 0 - exit code
 * The function operation: read conf file, finds c file for each student,
 * compiles, run and compare the output, and give grades.
*************************************************************************/
int main(int argc, char *argv[]) {
    //variable declaration
    int fdConf, sizeConf, depth = 0, fdResult, grade;
    char buffer[CONF_SIZE];
    char *dirPath, *inPath, *outPath;
    char subDirPath[PATH_SIZE], cFilePath[PATH_SIZE], result[CONF_SIZE],
            gradeStr[GRADE_SIZE];
    const char delim[2] = {'\n', '\r'};
    DIR *dir;
    struct dirent *dirent;

    //open configuration file
    fdConf = open(argv[1], O_RDONLY);
    if (fdConf < 0) {
        perror("open file not succeeded");
        exit(-1);
    }

    //read configuration file
    sizeConf = read(fdConf, buffer, 480);
    if (sizeConf < 0) {
        perror("error while reading from file");
        exit(-1);
    }

    //split configuration to 3 paths
    dirPath = strtok(buffer, delim);
    inPath = strtok(NULL, delim);
    outPath = strtok(NULL, delim);

    //open folder of student folders
    if ((dir = opendir(dirPath)) == NULL) {
        perror("error while open directory");
        exit(-1);
    }

    //create result.csv
    if ((fdResult = open("result.csv",O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0){
        perror("failed creation of result.csv file");
        exit(-1);
    }

    //loop on all subFolders
    while ((dirent = readdir(dir)) != NULL) {
        //clean buffers and depth variable
        memset(subDirPath, 0, PATH_SIZE);
        memset(cFilePath, 0, PATH_SIZE);
        memset(result,0,CONF_SIZE);
        depth = 0;
        //create subFlder path
        PathCreator(subDirPath, dirPath, dirent->d_name);
        //check it's a folder and not '.' or '..'
        if (IsLegalDir(subDirPath, dirent->d_name)) {
            //recursive function to find the c file
            FindCFile(cFilePath, subDirPath, &depth);
            //if cFilePath is path to c file
            if (strstr(cFilePath, "/")) {
                //compile it
                Compile(cFilePath);
                //if there was compiliation error - give '0'
                if (strcmp(cFilePath, "COMPILATION_ERROR") == 0){
                    WriteLine(result, dirent->d_name, "0", cFilePath, fdResult);
                } else {
                    //else, run the program with args and redirect to "studentOutput"
                    Run(inPath, cFilePath);
                    //if there was timeout while running - give '0'
                    if (strcmp(cFilePath, "TIMEOUT") == 0){
                        WriteLine(result, dirent->d_name, "0", cFilePath, fdResult);
                        //else - check student's output with the correct output
                    } else {
                        //compare student's output with the correct output
                        RunComp(cFilePath, outPath);
                        //calculate grade and write to result.csv
                        grade = CalcGrade(cFilePath, &depth);
                        sprintf(gradeStr,"%d",grade);
                        WriteLine(result, dirent->d_name, gradeStr, cFilePath, fdResult);
                    }
                }
                //in case there is no c file or multiple directories - give '0'
            } else {
                WriteLine(result, dirent->d_name, "0", cFilePath, fdResult);
            }
        }
    }
    //close file and directories
    if (closedir(dir) < 0){
        perror("failed to close directory");
        exit(-1);
    }
    if (close(fdConf) < 0){
        perror("failed to close file");
        exit(-1);
    }
    if (close(fdResult) < 0){
        perror("failed to close file");
        exit(-1);
    }
    //delete extra files
    if (unlink("student.out") < 0){
        perror("failed to remove file");
        exit(-1);
    }
    if (unlink("studentOutput") < 0){
        perror("failed to remove file");
        exit(-1);
    }
    return 0;
}

/************************************************************************
 * Function name: CalcGrade
 * The input: buffer and pointer to depth
 * The output: the updated grade
 * The function operation: check for wrong directory and output status
 * and gives grade.
*************************************************************************/
int CalcGrade(char *path, int *depth) {
    //variable declaration
    int grade;
    //calculate grade according to depth
    grade = 100 - (*depth * 10);
    //concatenate wrong directory to output
    if (strcmp(path, "GREAT_JOB") == 0) {
        if (*depth != 0) {
            strcat(path, ",WRONG_DIRECTORY");
        }
    }
    if (strcmp(path, "SIMILLAR_OUTPUT") == 0) {
        grade -= 30;
        if (*depth != 0) {
            strcat(path, ",WRONG_DIRECTORY");
        }
    }
    if (strcmp(path, "BAD_OUTPUT") == 0) {
        grade = 0;
        if (*depth != 0) {
            strcat(path, ",WRONG_DIRECTORY");
        }
    }
    //check for negative grade
    if (grade < 0){
        grade = 0;
    }
    return grade;
}

/************************************************************************
 * Function name: RunComp
 * The input: buffer and correct output path
 * The output: no output
 * The function operation: run comp.out on students output and correct
 * output
*************************************************************************/
void RunComp(char *path, char *outPath) {
    //variable declaration
    pid_t pid;
    int status, compare;
    //initialize buffer
    memset(path,0,PATH_SIZE);
    //new process for running comp.out
    if((pid = fork()) == 0){
        execlp("./comp.out", "comp.out", "studentOutput", outPath, NULL);
    }
    //check if fork failed
    if (pid < 0){
        perror("failed creating child process");
        exit(-1);
    }
    //chek the status
    if ((waitpid(pid,&status,0)) < 0){
        perror("error while calling wait()");
        exit(-1);
    }
    //check return value from comp.out
    if (WIFEXITED(status)){
        compare = WEXITSTATUS(status);
    }
    //write result to buffer
    switch (compare){
        case 1:
            strcpy(path,"GREAT_JOB");
            break;
        case 2:
            strcpy(path,"SIMILLAR_OUTPUT");
            break;
        case 3:
            strcpy(path, "BAD_OUTPUT");
            break;
        default:
            break;
    }
}

/************************************************************************
 * Function name: Run
 * The input: input file path and buffer
 * The output: no output
 * The function operation: runs student's program and checks for timeout
*************************************************************************/
void Run(char *inPath, char *cFilePath) {
    //variable declarations
    pid_t pid;
    int timeout, status, fdIn, fdOut;
    //initialize cFilePath
    memset(cFilePath,0,PATH_SIZE);
    //open studentOutput file
    fdOut = open("studentOutput", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fdOut < 0) {
        perror("open file not succeeded");
        exit(-1);
    }
    //open input file
    fdIn = open(inPath, O_RDONLY);
    if (fdIn < 0) {
        perror("open file not succeeded");
        exit(-1);
    }
    //new process for running
    pid = fork();
    if (pid < 0){
        perror("failed creating child process");
        exit(-1);
    }
    if (pid == 0){
        //redirect input from input file
        if((dup2(fdIn,0)) < 0){
            perror("dup2() failed");
        }
        //redirect input to output file
        if((dup2(fdOut, 1)) < 0){
            perror("dup2() failed");
        }
        //run student's program
        execlp("./student.out", "student.out", NULL);
    }
    //check for timeout
    timeout = 5;
    //check if every second the fork ended for 5 seconds
    while (timeout != 0){
        timeout--;
        sleep(1);
        //if the fork stopped
        if ((waitpid(pid, &status,WNOHANG)) != 0){
            break;
        }
    }
    //if it didn't stop, kill the fork, and write timeout
    if (timeout == 0){
        strcpy(cFilePath,"TIMEOUT");
        kill(pid,SIGSTOP);
    }
    if (close(fdOut) < 0) {
        perror("failed to close file");
        exit(-1);
    }
    if (close(fdIn) < 0) {
        perror("failed to close file");
        exit(-1);
    }
}

/************************************************************************
 * Function name: Compile
 * The input: path for compiling
 * The output: no output
 * The function operation: compiles students c file and check for
 * compilation error
*************************************************************************/
void Compile(char *cFilePath) {
    //variable declaration
    int status, fail;
    pid_t pid;
    //new process for compiling
    pid = fork();
    if (pid < 0){
        perror("failed creating child process");
        exit(-1);
    }
    //compile student's c file
    if (pid == 0){
        execlp("gcc", "gcc", cFilePath, "-o", "student.out", NULL);
    }
    //chek the status
    if ((wait(&status)) < 0){
        perror("error while calling wait()");
        exit(-1);
    }
    if (WIFEXITED(status)){
        fail = WEXITSTATUS(status);
        //if not compiled - notify
        if (fail){
            memset(cFilePath,0,strlen(cFilePath));
            strcpy(cFilePath,"COMPILATION_ERROR");
        }
    }
}

/************************************************************************
 * Function name: WriteLine
 * The input: buffer to line, student's name, grade, info, fd result.csv
 * The output: no output
 * The function operation: concatenate student's line and write to file
*************************************************************************/
void WriteLine(char *result, char *name, char *grade, char *info, int fd) {
    strcat(result, name);
    strcat(result, ",");
    strcat(result, grade);
    strcat(result, ",");
    strcat(result, info);
    strcat(result, "\n");
    if (write(fd,result,strlen(result)) < 0){
        perror("failed to write to file");
        exit(-1);
    }
}

/************************************************************************
 * Function name: FindCFile
 * The input: buffer to path, directory path, pointer to depth variable
 * The output: no output
 * The function operation: enter to directory, search for c file, if
 * more than one dir and no c file, or no c file at all writes to buffer
 * if finds c file, writes it to buffer
*************************************************************************/
void FindCFile(char *cFilePath, char *dirPath, int *depth) {
    //variable declaration
    int count = 0;
    DIR *dir;
    struct dirent *dirent;
    char newPath[PATH_SIZE], subDirPath[PATH_SIZE];
    //open subDirectory
    if ((dir = opendir(dirPath)) == NULL) {
        perror("error while open directory");
        exit(-1);
    }
    //loop on all files/directories in student's directory
    while ((dirent = readdir(dir)) != NULL) {
        //create path of file/directory
        PathCreator(newPath, dirPath, dirent->d_name);
        //if it's directory and not '.' or '..'
        if (IsLegalDir(newPath, dirent->d_name)) {
            //save the dir path and counter is updated
            strcpy(subDirPath, newPath);
            count++;
            //if it's file, find if it's c file and write it to buffer
        } else {
            if (IsCFile(dirent->d_name)) {
                strcpy(cFilePath, newPath);
                return;
            }
        }
        //initialize buffer before enters to recurrsion
        memset(newPath,0,strlen(newPath));
    }
    if (closedir(dir) < 0){
        perror("failed to close directory");
        exit(-1);
    }
    //if didn't find c file and no sub directories
    if (count == 0) {
        strcpy(cFilePath, "NO_C_FILE");
        return;
    }
    //if found more than one directory and no c file
    if(count > 1) {
        strcpy(cFilePath, "MULTIPLE_DIRECTORIES");
        return;
    }
    //if found one directory and no c file, send recurrsively
    *depth = *depth + 1;
    return FindCFile(cFilePath, subDirPath, depth);
}

/************************************************************************
 * Function name: IsLegalDir
 * The input: path and folder name
 * The output: 1 for true, 0 for false
 * The function operation: check if it's directory and not '.' or '..'
 * or hidden directory
*************************************************************************/
int IsLegalDir(char *path, char *name) {
    //variable declaration
    struct stat statBuf;
    int statSuccess;
    //check path ststus
    statSuccess = stat(path, &statBuf);
    if (statSuccess < 0) {
        perror("failed in stat");
    }
    //if it's directory and not '.' or '..' or hidden directory return true
    if (S_ISDIR(statBuf.st_mode) && strcmp(name, ".") != 0
        && strcmp(name, "..") != 0) {
        return 1;
    }
    //else return false
    return 0;
}

/************************************************************************
 * Function name: IsCFile
 * The input: name of file
 * The output: 1 for true, 0 for false
 * The function operation: check if the extension of the file is '.c'
*************************************************************************/
int IsCFile(char *name) {
    //variable declaration
    char *extension;
    //get the extension
    extension = strrchr(name, '.');
    //check if there is '.' in the name of the file
    if (extension != NULL && strcmp(extension, name) != 0) {
        //if the extension is .c - true
        if (strcmp(".c", extension) == 0) {
            return 1;
        }
    }
    //else - false
    return 0;
}

/************************************************************************
 * Function name: PathCreator
 * The input: buffer to write, the path and the dir/file name
 * The output: no output
 * The function operation: concatenate the path and the dir/file name
*************************************************************************/
void PathCreator(char *buffer, char *path, char *dir) {
    //concatenate the path and the dir/file name
    strcpy(buffer, path);
    strcat(buffer, "/");
    strcat(buffer, dir);
}