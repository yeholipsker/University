
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main() {
    int n1, n2;
    printf("Please enter two numbers\n");
    while (1) {
        scanf("%d %d", &n1, &n2);
        printf("%d", n1 + n2);
    }
}
