#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void timer_handler(int signum) {
    printf("Timer expired.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct itimerval timer;
    struct sigaction sa;

    // Set up the signal handler
    sa.sa_handler = timer_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Set timer expiration
    timer.it_value.tv_sec = 10;         // 10 seconds
    timer.it_value.tv_usec = 10000;     // 10 microseconds

    // Set timer interval to 0 to make it a one-shot timer
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Start the timer
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // Wait for the timer to expire
    while (1) {
        // Do nothing
    }

    return 0;
}
