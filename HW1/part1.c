#include <stdio.h>
#include <sys/types.h>
int main( int argc, char* argv[]) {
	int N = 0;
	int pid;
	if(argc==1){
		printf("Error Command Line Argument N not provided, run program like: \n./part1 <N>\nWhere N is a integer \n");
		return 0;
	}else{
		char *c = argv[1];
		N = atoi(c);
	}

	int pid0 = fork();
	if (pid0 == 0){
		//child 1
		for (int i = 0; i < N; i++){
			printf("This is a child process, my PID is %d, my parent PID is %d\n", getpid(), getppid());
			sleep(2);
		}
	}else{
		int pid1 = fork();
		if (pid1 == 0){
			//child 2
			for (int j = 0; j < N; j++){
				printf("This is a child process, my PID is %d, my parent PID is %d\n", getpid(), getppid());
				sleep(2);
			}
		}else{
			int pid2 = fork();
			if (pid2 == 0){
				//child 3
				for (int k = 0; k < N; k++){
					printf("This is a child process, my PID is %d, my parent PID is %d\n", getpid(), getppid());
    					sleep(2);
				}
			}else{
				for (int l = 0; l < N; l++){
					//parent
					printf("This is the main process, my PID is %d\n", getpid());
					sleep(2);
				}
			}
		}
	}
	return 0;
}
