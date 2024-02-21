/*
 File Writing by Parent and Child Processes: Develop a program that opens a file, calls fork, 
and allows both the child and parent processes to write to the file. Examine the output of 
the file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    // Open a file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        // Error occurred
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        fprintf(file, "Child process writing to the file\n");
        fclose(file);
        exit(0);
    } else {
        // Parent process
        fprintf(file, "Parent process writing to the file\n");
        fclose(file);
        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}
