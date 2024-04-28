#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){   //using fcntl
    int fd[2];
    pipe(fd);
    int x=fork();
    if(x==0){
        close(1);
        close(fd[0]);
        fcntl(fd[1],F_DUPFD);
        execlp("ls","ls","-l",NULL);
    }
    else{
        close(0);
        close(fd[1]);
        fcntl(fd[0],F_DUPFD);
        execlp("wc","wc",NULL);
    }

}