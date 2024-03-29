#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>

int main() {
    // Get maximum number of files that can be opened within a process
    struct rlimit file_limit;
    if (getrlimit(RLIMIT_NOFILE, &file_limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Maximum number of files that can be opened within a process: %lld\n", (long long)file_limit.rlim_cur);

    // Get size of a pipe (circular buffer)
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pipe_size = fpathconf(pipefd[0], _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("fpathconf");
        exit(EXIT_FAILURE);
    }

    printf("Size of a pipe (circular buffer): %d bytes\n", pipe_size);

    return 0;
}
