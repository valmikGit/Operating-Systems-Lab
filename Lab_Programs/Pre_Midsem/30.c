/*
Running a Script at a Specific Time with a Daemon Process: Create a program to execute a 
task at a specific time using a Daemon process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

int main(){
    int q = fork();
    if(q) return 0;
    printf("Daemon process was initialized with PID %d\n",getpid());
    setsid();
    chdir("/");
    umask(0);
    close(0);
    close(1);
    close(2);
    while(1);
}
