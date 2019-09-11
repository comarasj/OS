#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char* file_name;
	if (argc == 1) {
		printf("Invalid command line syntax, run program like:\npart2 <file_name>\nWhere file_name is a file ");
		return 0;
	}else{
		file_name = argv[1];
		printf("%s\n", file_name);
		processes(file_name);
	}
	return 0;

}
void processes(char* file_name ) {
	int pid0 = fork();
	if (pid0 == 0){
		//child 0
		execl("/bin/ls", "ls", "-l", (char*) NULL);
	}else{
		int pid1 = fork();
		if (pid1 == 0){
			//child 1
			execl("/bin/ps", "ps", "-ef", (char*) NULL);
		}else{
			int pid2 = fork();
			if(pid2 == 0){
				execl("/bin/more", "more", file_name, (char*) NULL);
			}else{
				printf("This is the main process, my PID is %d\n", getpid());
				wait();
				wait();
				wait();
				printf("main process terminates\n");
			}
		}
	}
}
