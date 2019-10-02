#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

const int SHM_SIZE = 1024;  /* make it a 1K shared memory segment */
const char FILE_NAME[] = "shared.dat";
const int MAXLINE = 255;

int main(int argc, char *argv[])
{
	key_t key;
	int shmid;
	char *data;
	char line[MAXLINE];
	int n;
	FILE *fp;

	/* make the key: */
	if ((key = ftok(FILE_NAME, 1)) == -1) {
		perror("ftok");
        	return 0;
    	}

   	 /* connect to (and possibly create) the segment: */
   	 if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        	perror("shmget");
        	return 0;
    	}
 	/* attach to the segment to get a pointer to it: */
	data = shmat(shmid, (void *)0, 0);
    	if (data == (char *)(-1)) {
        	perror("shmat");
        	return 0;
	}

	/* modify the segment, based on the command line: */
	fp = fopen("part3.txt", "r");
	while (fgets(line, MAXLINE, fp) != NULL){
		for (int i = 0; i < MAXLINE; i++){
			if (line[i] >= 'a' && line[i] <= 'z'){
				line[i] = line[i] - 32;
			}
		}
		strncpy(data, line, SHM_SIZE);
		printf("%s", line);
		sleep(1);
	}
	fclose(fp);

	strncpy(data, "STOP", SHM_SIZE);

	/* detach from the segment: */
	if (shmdt(data) == -1) {
        	perror("shmdt");
        	return 0;
	}
	return 0;
}

