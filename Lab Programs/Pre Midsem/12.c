#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

/*
Determining Opening Mode of a File: Create a program to find out the opening mode of a 
file using the fcntl system call.
*/

int main()
{
    char File_Name[100];
    printf("Enter the file name: ");
    scanf("%s", File_Name);
    int fd = open(File_Name, O_RDWR | O_APPEND);
    int x = fcntl(fd, F_GETFL);
    close(fd);
    printf("x = %d\n", x);
    if (x & O_RDONLY) // Done
    {
        printf("O_RDONLY\n");
    }
    else if (x & O_WRONLY) // Done
    {
        printf("O_WRONLY\n");
    }
    else if (x & O_RDWR ) // Done
    {
        printf("O_RDWR\n");
    }
    else if (x & O_WRONLY && x & O_APPEND) // Done
    {
        printf("O_WRONLY | O_APPEND\n");
    }
    else if (x & O_RDWR && x & O_APPEND) // Done
    {
        printf("O_RDWR | O_APPEND\n");
    }
    else
    {
        printf("Unknown mode\n");
    }
}