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
    char hard_File[1000];
    printf("Enter the file name.\n");
    scanf("%s", entered_Name);
    printf("Enter the hard link name.\n");
    scanf("%s", hard_File);
    int x = link(entered_Name, hard_File);
    printf("Return value = %d\n");
}