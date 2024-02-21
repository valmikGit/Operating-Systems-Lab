#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*
 Creating Different File Types: Utilize both shell commands and system calls to create the 
following types of files:
a. soft link (using the symlink system call)
b. hard link (using the link system call)
c. FIFO (using either the mkfifo Library Function or the mknod system call)
*/

int main() {
    char entered_Name[1000];
    char fifo_File[1000];
    printf("Enter the file name.\n");
    scanf("%s", entered_Name);
    int x = mknod(entered_Name, S_FIFO, 0);
    printf("Return value = %d\n", x);
}