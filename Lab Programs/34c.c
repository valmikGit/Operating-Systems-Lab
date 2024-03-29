#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end

        // Redirect stdout to the write end of the pipe
        if (fcntl(pipefd[1], F_SETFD, O_WRONLY) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end

        // Redirect stdin to the read end of the pipe
        if (fcntl(pipefd[0], F_SETFD, O_RDONLY) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }

        // Execute wc
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
