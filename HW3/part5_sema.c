#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define KEY 0x1111

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

struct sembuf p = { 0, -1, SEM_UNDO};
struct sembuf v = { 0, +1, SEM_UNDO};

const int SHM_SIZE = 1024;
const char FILE_NAME[] = "shared.dat";
const int MAXLINE = 255;

int main()
{
    key_t key;
    int shmid;
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    char *data;

    if ((key = ftok(FILE_NAME, 1)) == -1){
        perror("ftok");
        return 0;
    }
    
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1){
        perror("shmget");
        return 0;
    }

    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)){
        perror("shmat");
        return 0;
    }

    if(id < 0)
    {
        perror("semget"); exit(11);
    }
    union semun u;
    u.val = 1;
    if(semctl(id, 0, SETVAL, u) < 0)
    {
        perror("semctl"); exit(12);
    }
    int pid;
    pid =  fork();
    srand(pid);
    if(pid < 0)
    {
        perror("fork"); exit(1);
    }
    else if(pid)
    {
        const char *s = "abcdefgh";
        int l = strlen(s);
        for(int i = 0; i < l; ++i)
        {
            if(semop(id, &p, 1) < 0)
            {
                perror("semop p"); exit(13);
            }

            strncpy(data, "A", SHM_SIZE);
            printf("A");
            sleep(rand() % 2);
            strncpy(data, "A", SHM_SIZE);
            printf("A");
            sleep(rand() % 2);
            
            if(semop(id, &v, 1) < 0)
            {
                perror("semop p"); exit(14);
            }

            sleep(rand() % 2);
        }
    }
    else
    {
        const char s[] = "ABCDEFGH";
        int l = strlen(s);
        for(int i = 0; i < l; ++i)
        {
            if(semop(id, &p, 1) < 0)
            {
                perror("semop p"); exit(15);
            }

            strncpy(data, "a", SHM_SIZE);
            printf("a");
            sleep(rand() % 2);
            strncpy(data, "a", SHM_SIZE);
            printf("a");
            sleep(rand() % 2);
            if(semop(id, &v, 1) < 0)
            {
                perror("semop p"); exit(16);
            }

            sleep(rand() % 2);
        }
    }
}