#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
//client side
int main(){
    int sock_fd=socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd==0){
        perror("socket");
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=INADDR_ANY;
    if(connect(sock_fd,(struct sockaddr*)&server,sizeof(server))<0){
        perror("connect");
        return -1;
    }
    char buffer[1024];
    recv(sock_fd,buffer,1024,0);
    printf("Received %s\n",buffer);
    send(sock_fd,"Hello from client",1024,0);
    return 0;
}