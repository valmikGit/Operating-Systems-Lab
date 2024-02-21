#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

/*
File Information Extraction: Create a program to print various details about a given file, 
including:
a. Inode
b. Number of hard links
c. UID
d. GID
e. Size
f. Block size
g. Number of blocks
h. Time of last access
*/

int main() {
    struct stat st;
    stat("xyz", &st);
    printf("Inode number: %d\n", st.st_ino);
    printf("Number of hard links: %ld\n", st.st_nlink);
    printf("UID = %d\n", st.st_uid);
    printf("GID = %d\n", st.st_gid);
    printf("Size = %ld\n", st.st_size);
    printf("Block size = %ld\n", st.st_blksize);
    printf("Number of blocks = %ld\n", st.st_blocks);
    printf("Time of last access = %ld\n", st.st_atime.tv_sec);
    printf("Time of last modification = %ld\n", st.st_mtime.tv_sec);
    printf("Time of last change = %ld\n", st.st_ctime.tv_sec);
}