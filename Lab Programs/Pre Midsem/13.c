#include<stdio.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>

/*
Waiting for STDIN Using Select: Develop a program to wait for input from STDIN for 10 
seconds using select. Include proper print statements to verify data availability within the 
specified time.
*/

int main() {
    struct timeval t;
    t.tv_sec = 10;
    t.tv_usec = 0;
    fd_set read;
    FD_ZERO(&read);
    FD_SET(0, &read);
    int return_Value = select(1, &read, NULL, NULL, &t);
    if (return_Value == 0)
    {
        printf("Data not available\n");
    }
    else if (return_Value > 0)
    {
        printf("Data is available.\n");
    }
}