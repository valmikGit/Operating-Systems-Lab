#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*
File Copying: Develop a program to copy the contents of file1 into file2, emulating the 
behavior of the $cp file1 file2 command.
*/

int main() {
    char file_Name_1[100];
    char file_Name_2[100];
    char buffer[100];
    for (int i = 0; i < 100; i++)
    {
        strcpy(&buffer[i], "");
    }
    printf("Enter the file name: ");
    scanf("%s", file_Name_1);
    int fd_1 = open(file_Name_1, O_RDONLY);
    int x = read(fd_1, buffer, sizeof(buffer));
    printf("Enter the file name: ");
    scanf("%s", file_Name_2);
    int fd_2 = open(file_Name_2, O_WRONLY);
    int y = write(fd_2, buffer, sizeof(buffer));
}