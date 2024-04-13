#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    struct rlimit rlim;

    // Define the soft and hard limits
    rlim.rlim_cur = 1000000;  // Soft limit: 1 million
    rlim.rlim_max = 1000000;  // Hard limit: 1 million

    // Set the resource limit for maximum number of open files (RLIMIT_NOFILE)
    if (setrlimit(RLIMIT_NOFILE, &rlim) == -1) {
        perror("setrlimit");
        return 1;
    }

    printf("Resource limit set successfully.\n");

    return 0;
}
