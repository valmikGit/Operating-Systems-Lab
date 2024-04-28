#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

// Ignore this comment.

int main() {
    int pipefd[2]; // File descriptors for the pipe
    char buffer[BUFFER_SIZE];
    pid_t child_pid;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe

        // Read from the pipe
        ssize_t num_bytes = read(pipefd[0], buffer, BUFFER_SIZE);
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Display the content received from the pipe
        printf("Child process received: %s", buffer);

        close(pipefd[0]); // Close the read end of the pipe in the child
    } else {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        // Write to the pipe
        const char *message = "Hello, child process!\n";
        if (write(pipefd[1], message, strlen(message) + 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close the write end of the pipe in the parent
    }

    return 0;
}
