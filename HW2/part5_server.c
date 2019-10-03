#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

const int MAXLINE = 1024;

int main(int argc, char * argv[]) {
    int fd;
    int * map;
    char * data;
    if ((fd = open("shared", O_RDWR | O_CREAT)) < 0){
        printf("Unable to open file.");
        return 1;
    }
    ftruncate(fd, MAXLINE);
    if ((map = (int*) mmap(0, MAXLINE, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED){
        printf("mmap failed");
        return 1;
    }
    data = (char*) map + 4;
    int n = -1; //variable to check if same value was already read
    while (1) {
        if (n == map[0]) {
            continue;
        }
        n = map[0];
        if (strcmp(data, "STOP") == 0)
            break;
        printf("%s", data);
    }
    unlink("shared");
}
