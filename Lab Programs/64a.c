#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigstop_handler(int signum) {
    printf("Caught SIGSTOP\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigstop_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGSTOP, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Waiting for SIGSTOP signal...\n");
    while (1) {
        sleep(1); // Sleep to avoid CPU usage
    }

    return 0;
}
