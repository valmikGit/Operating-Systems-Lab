#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
File Creation and Descriptor Printing: Write a program in C that creates a file and prints its file 
descriptor value using the creat() system call.
*/

int main() {
    // Create a file named "example.txt" with read, write and execute permissions
    int fd = creat("example.txt", 0666);
    
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    printf("File created successfully with descriptor: %d\n", fd);
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}
