#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

/*
Mandatory Locking Implementation: Write a program to perform mandatory locking with 
the following implementations: 
a. Implement a write lock. 
b. Implement a read lock.
*/

int main() {
    char file_Name[100];
    scanf("%s", file_Name);
    int fd = open(file_Name, O_RDONLY);

    printf("Lock Setting\n");
    struct flock lk;
    lk.l_type = F_RDLCK;
    lk.l_pid = getpid();
    lk.l_start = 0;
    lk.l_whence = SEEK_SET;
    lk.l_len = 0;

    int x = fcntl(fd, F_SETLKW, &lk);
    printf("%d\n", x);
    printf("Press enter to unlock\n");
    while (getchar() != '\n')
    {
        getchar();
    }
    lk.l_type = F_UNLCK;
    int y = fcntl(fd, F_SETLKW, &lk);
    printf("%d\n", y);
    printf("Unlocked\n");

    close(fd);
}