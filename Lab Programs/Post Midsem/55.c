#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit r_limit;

    // Get the current limits
    if (getrlimit(RLIMIT_NOFILE, &r_limit) == 0) {
        printf("Current soft limit for number of open files: %ld\n", r_limit.rlim_cur);
        printf("Current hard limit for number of open files: %ld\n", r_limit.rlim_max);
    } else {
        perror("getrlimit");
        return 1;
    }

    // Set new limits
    r_limit.rlim_cur = 1024; // Soft limit
    r_limit.rlim_max = 2048; // Hard limit

    if (setrlimit(RLIMIT_NOFILE, &r_limit) == 0) {
        printf("New soft limit for number of open files: %ld\n", r_limit.rlim_cur);
        printf("New hard limit for number of open files: %ld\n", r_limit.rlim_max);
    } else {
        perror("setrlimit");
        return 1;
    }

    return 0;
}
