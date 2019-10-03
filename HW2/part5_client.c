#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

const int MAXLINE = 1024;

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Expected one argument. Received %d arguments.\n", argc-1);
        printf("Proper usage: <program> <file_name>\n");
        exit(1);
    }
    char line[MAXLINE];
    int fd;
    int * map;
    char * data;

    FILE * fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File not found.");
        return 1;
    }
    if ((fd = open("shared", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0){
        printf ("Error opening file for writing.");
        return 1;
    }
    ftruncate(fd, MAXLINE);

    if ((map = (int*)mmap(0, MAXLINE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        printf ("mmap output error");
        return 1;
    }
    data = (char*)map + 4;

    while(fgets(line, MAXLINE, fp) != NULL) {
        for (int i = 0; i < MAXLINE; i++){
		if (line[i] >= 'a' && line[i] <= 'z'){
			line[i] = line[i] - 32;
		}
	}
        strncpy(data, line, MAXLINE);
        printf("%s", data);
        ++*map;
        sleep(1);
    }
    strncpy(data, "STOP", 5);
    ++*map;
    printf("STOP\n");
    munmap(map, MAXLINE);
    close(fd);
    return 0;
}
