#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    struct rlimit rlim; 

    rlim.rlim_cur = 1000000; // allows a soft limit of 1M file descriptors that the process can open.
    rlim.rlim_max = 1000000; // allows a hard limit of 1M file descriptors that the process can open.

    setrlimit(RLIMIT_NOFILE, &rlim) == -1;  ///set current max 1M open files by the processes.

    struct rlimit rlim2;
    getrlimit(RLIMIT_NOFILE, &rlim2); //get current max open files

    printf("Resource limit's, current value is %ld and max value is\n", rlim2.rlim_cur);

    return 0;
}