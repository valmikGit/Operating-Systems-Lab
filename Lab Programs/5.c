#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Continuous File Creation: Create a program that generates five new files in an infinite loop. 
Execute the program in the background and inspect the file descriptor table at /proc/pid/fd.

*/

int main()
{
    int x1 = creat("abc1", 0744);
    int x2 = creat("abc2", 0744);
    int x3 = creat("abc3", 0744);
    int x4 = creat("abc4", 0744);
    int x5 = creat("abc5", 0744);
    printf("fd1 = %d\nfd2 = %dfd3 = %d\nfd4 = %d\nfd5 = %d\n", x1, x2, x3, x4, x5);
    while (1)
    {
    }
}