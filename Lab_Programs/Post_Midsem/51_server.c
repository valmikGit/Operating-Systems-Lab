/*
Program Number : 33 - server
Name : Vidhish Trivedi
Register Number : IMT2021055
Date : 08/04/2023
Description : Server program to communicate between two machines using socket.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    struct sockaddr_in serv, cli;
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
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
    if(bind(sock_fd,(struct sockaddr*)&server,sizeof(server))<0){
        perror("bind");
        return -1;
    }
    if(listen(sock_fd,1)<0){
        perror("listen");
        return -1;
    }
    while (1)
    {
        struct sockaddr_in client;
        socklen_t client_len=sizeof(client);
        int newfd=accept(sock_fd,(struct sockaddr*)&client,&client_len);
        if(newfd<0){
            perror("accept");
            return -1;
        }
        char buffer[1024]="Hello from server";
        send(newfd,buffer,1024,0);
        recv(newfd,buffer,1024,0);
        printf("Received %s from %s\n",buffer,inet_ntoa(client.sin_addr));
    }
    

}
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5000);
    
    bind(sd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sd, 5);

    int nsd;

    int len = sizeof(cli);
    nsd = accept(sd, (struct sockaddr *)&cli, &len);

    char buf[100];
    int ret;
    ret = read(nsd, buf, sizeof(buf));
    write(1, buf, ret);
    write(nsd, "Message From server\n", sizeof("Message From server\n"));

    close(sd);

    return(0);
}