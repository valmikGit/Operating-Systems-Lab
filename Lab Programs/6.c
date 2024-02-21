#include<unistd.h>
#include<stdio.h>
#include<string.h>

/*
Input and Output Using System Calls: Craft a program to take input from STDIN and display 
it on STDOUT using only read/write system calls.
*/

int main() {
    char buffer[100];
    for (int i = 0; i < 100; i++)
    {
        strcpy(&buffer[i], "");
    }
    int x = read(0, &buffer, 100);
    int y = write(1, &buffer, 100);
}