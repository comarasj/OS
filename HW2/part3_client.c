#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char* argv[]) {
	const int MAXLINE = 255;
	char line[MAXLINE];
	int fd;
	char* myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	FILE *fp;
	fd = open(myfifo, O_WRONLY);
	fp = fopen("part3.txt", "r");
	while (fgets(line, MAXLINE, fp) != NULL){
		write(fd, line, MAXLINE);
		printf("%s", line);
		sleep(1);
	}
	write(fd, "Stop\n", MAXLINE);

	fclose(fp);
	close(fd);
	return 0;
}
