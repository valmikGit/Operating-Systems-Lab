#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

/*
File Type Identification: Write a program that takes input from the command line and 
identifies the type of file. Ensure the program can recognize various file types
*/

int main(int argc, char * argv[]) {
    struct stat st;
    stat(argv[1], &st);
    switch (st.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("Block device\n");
        break;
    
    case S_IFCHR:
        printf("Character device\n");
        break;
    
    case S_IFDIR:
        printf("directory\n");
        break;
    
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;

    case S_IFLNK:
        printf("symlink\n");
        break;

    case S_IFREG:
        printf("Regular file\n");
        break;

    case S_IFSOCK:
        printf("Socket\n");
        break;

    default:
        printf("Unknown?\n");
        break;
    }
}