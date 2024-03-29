#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int parent_to_child_pipe[2]; // Pipe for communication from parent to child
    int child_to_parent_pipe[2]; // Pipe for communication from child to parent
    char buffer[BUFFER_SIZE];
    pid_t child_pid;

    // Create pipes
    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
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
        close(parent_to_child_pipe[1]); // Close the write end of the parent-to-child pipe
        close(child_to_parent_pipe[0]); // Close the read end of the child-to-parent pipe

        // Read from the parent-to-child pipe
        ssize_t num_bytes = read(parent_to_child_pipe[0], buffer, BUFFER_SIZE);
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Display the content received from the parent
        printf("Child process received from parent: %s", buffer);

        // Write a response to the parent
        const char *response = "Message received by child process!\n";
        if (write(child_to_parent_pipe[1], response, strlen(response) + 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(parent_to_child_pipe[0]); // Close the read end of the parent-to-child pipe
        close(child_to_parent_pipe[1]); // Close the write end of the child-to-parent pipe
    } else {
        // Parent process
        close(parent_to_child_pipe[0]); // Close the read end of the parent-to-child pipe
        close(child_to_parent_pipe[1]); // Close the write end of the child-to-parent pipe

        // Write to the parent-to-child pipe
        const char *message_to_child = "Hello, child process!\n";
        if (write(parent_to_child_pipe[1], message_to_child, strlen(message_to_child) + 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Read response from the child
        ssize_t num_bytes = read(child_to_parent_pipe[0], buffer, BUFFER_SIZE);
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Display the content received from the child
        printf("Parent process received from child: %s", buffer);

        close(parent_to_child_pipe[1]); // Close the write end of the parent-to-child pipe
        close(child_to_parent_pipe[0]); // Close the read end of the child-to-parent pipe
    }

    return 0;
}
