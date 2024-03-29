#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    if (kill(pid, SIGSTOP) == -1) {
        perror("kill");
        return 1;
    }

    printf("SIGSTOP signal sent to process with PID %d\n", pid);

    return 0;
}
