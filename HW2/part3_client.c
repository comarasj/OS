#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char* argv[]) {
	if (argc != 2) {
        	printf("Expected one argument. Received %d arguments.\n", argc-1);
        	printf("Proper usage: <program> <file_name>\n");
        	return 1;
    	}
	const int MAXLINE = 255;
	char line[MAXLINE];
	int fd;
	char* myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	FILE *fp;
	fd = open(myfifo, O_WRONLY);
	fp = fopen(argv[1], "r");
	while (fgets(line, MAXLINE, fp) != NULL){
		for (int i = 0; i < MAXLINE; i++){
			if (line[i] >= 'a' && line[i] <= 'z'){
				line[i] = line[i] - 32;
			}
		}
		write(fd, line, MAXLINE);
		printf("%s", line);
		sleep(1);
	}
	write(fd, "STOP\n", MAXLINE);
	printf("STOP\n");
	fclose(fp);
	close(fd);
	return 0;
}
