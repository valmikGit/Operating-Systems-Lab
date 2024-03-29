#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the duplicated write end
        close(pipefd[1]);

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);

        // Close the duplicated read end
        close(pipefd[0]);

        // Execute wc
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
