#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_ls[2];
    int pipe_grep[2];
    pid_t pid_ls, pid_grep;

    // Create pipes
    if (pipe(pipe_ls) == -1 || pipe(pipe_grep) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork ls process
    pid_ls = fork();
    if (pid_ls == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_ls == 0) {
        // Child process for ls
        // Redirect stdout to the write end of pipe_ls
        dup2(pipe_ls[1], STDOUT_FILENO);
        close(pipe_ls[0]); // Close the read end of pipe_ls

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Fork grep process
        pid_grep = fork();
        if (pid_grep == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid_grep == 0) {
            // Child process for grep
            // Redirect stdin from pipe_ls and stdout to the write end of pipe_grep
            dup2(pipe_ls[0], STDIN_FILENO);
            close(pipe_ls[1]); // Close the write end of pipe_ls

            dup2(pipe_grep[1], STDOUT_FILENO);
            close(pipe_grep[0]); // Close the read end of pipe_grep

            // Execute grep ^d
            execlp("grep", "grep", "^d", NULL);
            perror("execlp grep");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            // Redirect stdin from pipe_grep
            dup2(pipe_grep[0], STDIN_FILENO);
            close(pipe_grep[1]); // Close the write end of pipe_grep

            // Execute wc
            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
