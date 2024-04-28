#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*
 Read-Only File Reading: Write a program to open a file in read-only mode, read line by line, 
and display each line as it is read. Close the file upon reaching the end of the file.
*/

int main() {
    int fd_1;
    char buffer[100];
    fd_1 = open("xyz1", O_RDONLY | O_EXCL);
    while (read(fd_1, buffer, 1) > 0)
    {
        if (buffer[0] == '\n')
        {
            int x = getchar();
        }
        else
        {
            printf("%s", buffer);
        }
    }
    int c = close(fd_1);
}