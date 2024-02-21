#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*
 Opening Existing File: Write a program to open an existing file in read-write mode. 
Experiment with the O_EXCL flag.
*/

int main() {
    char entered_Name[1000];
    printf("Enter the file name:");
    scanf("%s", entered_Name);
    int x = open(entered_Name, O_EXCL|O_RDWR);
    printf("fd = %d\n", x);
}