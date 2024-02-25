#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

/*
Determining Opening Mode of a File: Create a program to find out the opening mode of a 
file using the fcntl system call.
*/

int main() {
    char file_Name[100];
    printf("Enter the file name: ");
    scanf("%s", file_Name);
    int fd = open(file_Name, O_RDWR | O_APPEND);
    int x = fcntl(fd, F_GETFL);
    close(fd);
    printf("x = %d\n", x);
    if (x == 0) // Done
    {
        printf("O_RDONLY\n");
    }
    else if (x == 1) // Done
    {
        printf("O_WRONLY\n");
    }
    else if (x == 2) // Done
    {
        printf("O_RDWR\n");
    }
    else if (x == 1025) // Done
    {
        printf("O_WRONLY | O_APPEND\n");
    }
    else if (x == 1026) // Done
    {
        printf("O_RDWR | O_APPEND\n");
    }
    else
    {
        printf("Unknown mode\n");
    }
}