#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // Generate a unique key
    if ((key = ftok(".", 'X')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write some data to shared memory
    strcpy(shmaddr, "Hello, shared memory!");

    printf("Data written to shared memory: %s\n", shmaddr);

    // Attach the shared memory segment with O_RDONLY
    if ((shmaddr = shmat(shmid, NULL, SHM_RDONLY)) == (char *) -1) {
        perror("shmat O_RDONLY");
        exit(1);
    }

    printf("Data in read-only mode: %s\n", shmaddr);

    // Detach the shared memory segment
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
