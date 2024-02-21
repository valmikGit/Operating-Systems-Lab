#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

/*
File Write and Seek: Implement a program to open a file in read-write mode, write 10 
bytes, move the file pointer by 10 bytes using lseek, and then write another 10 bytes. 
a. Check the return value of lseek. 
b. Open the file with od command and examine the empty spaces between the data
*/

int main() {
    char file_Name[1000];
    char buffer[1000];
    printf("Enter the file name: ");
    scanf("%s", file_Name);
    printf("Enter: ");
    scanf("%[^\n]", buffer);
    int fd = open(file_Name, O_RDWR);
    int x = write(fd, buffer, 10);
    int y = lseek(fd, 10L, SEEK_CUR);
    printf("Enter: ");
    scanf("%[^\n]", buffer);
    int z = write(fd, buffer, 10);
    printf("First write: %d lseek: %d second write: %d\n", x, y, z);
    close(fd);
}