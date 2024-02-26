#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

/*
 Online Ticket Reservation Simulation: Develop a program to simulate online ticket 
reservation with the implementation of a write lock. Write one program to open a file, store 
a ticket number, and exit. Write a separate program to open the file, implement a write 
lock, read the ticket number, increment the number, print the new ticket number, and then 
close the file.

*/

int main() {
    int fd = open("ticket.txt", O_RDWR| O_CREAT,0644);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Inside critical section\n");
    fcntl(fd, F_SETLKW, &lock);
    int tokennum = 0;
    lseek(fd, 0, SEEK_SET);
    read(fd, &tokennum, sizeof(int));
    tokennum++;

    printf("Token number is: %d\n", tokennum);
    lseek(fd, 0, SEEK_SET);
    write(fd, &tokennum, sizeof(int));
    printf("Critical section end\n");
    printf("Enter to unlock");
    getchar();
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Unlock successful\n");
    close(fd);
}