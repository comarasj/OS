#include <stdio.h>
#include <sys/types.h>
#include <string.h>
int main( int argc, char* argv[]) {
	const int MAXLINE = 80;
	char line1[MAXLINE];
	FILE *fp = popen("find *.c", "r");
	FILE *up = popen("find *.c | tr a-z, A-Z", "r");
	if (!up) {
		printf("Error running command.. Exiting..");
		return 0;
	}
	while (fgets(line1, MAXLINE, up) != NULL){
		printf("%s", line1);
	}
	pclose(fp);
	pclose(up);
}

