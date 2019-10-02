#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

const int SHM_SIZE = 1024;  /* make it a 1K shared memory segment */
const char FILE_NAME[] = "shared.dat";

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int n;

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

    /* read the segment */
    n = 0;
    while ( (strcmp(data, "STOP") != 0) )
    {
        printf("%s", data);
        sleep(1);   /* Sleep 1 seconds) */
    }

    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        return 0;
    }

    /* delete the IPC structure */
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}


