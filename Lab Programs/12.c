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
    int fd = open(file_Name, O_RDWR);
    int x = fcntl(fd, F_GETFL);
    close(fd);
    printf("x = %d\n", x);
    if (x == 32768)
    {
        printf("O_RDONLY\n");
    }
    else if (x == 32769)
    {
        printf("O_WRONLY");
    }
    else if (x == 32770)
    {
        printf("O_RDWR\n");
    }
    else if (x == 32793)
    {
        printf("O_WRONLY | O_APPEND\n");
    }
    else if (x == 32794)
    {
        printf("O_RDWR | O_APPEND");
    }
    else
    {
        printf("Unknown mode");
    }
}