#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char* argv[]) {
	char *program_name, *file_name;
	int pid;
	if(argc <= 2){
		printf("Incorrect Program Usage, Please run program like: \npart1 /bin/ps  myresult.txt\n");
		return 0;
	}else{
		program_name = argv[1];
		file_name = argv[2];
	}
	int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0){
		//child
		close(1);
		dup(fd);
		execlp(program_name, program_name, NULL);
	}else{
		close(fd);
		wait(NULL);
	}
	return 0;
}
