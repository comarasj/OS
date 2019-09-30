#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main( int argc, char* argv[]) {
	const int MAXLINE = 255;
	char line[MAXLINE];
	int fd;
	char* myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	FILE *fp;
	fd = open(myfifo, O_RDONLY);
	while(1) {
		read(fd, line, sizeof(line));
		printf("%s", line);
		if (!strcmp(line, "Stop\n")){
			break;
		}
	}
	close(fd);
	remove("tmp/myfifo");
	return 0;

}
