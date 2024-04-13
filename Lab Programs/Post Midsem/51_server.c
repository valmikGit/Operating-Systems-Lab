#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>

int main() {
    struct sockaddr_in server, client;
    int sd, sz, nsd;
    char buff[80];

    sd = socket(AF_UNIX, SOCK_STREAM, 0);

    server.sin_family = AF_UNIX;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htonl(5555);

    bind(sd, (struct sockaddr *)(&server), sizeof(server));

    listen(sd, 5);

    sz = sizeof(client);
    nsd = accept(sd, (struct sockaddr*)(&client), &sz);

    read(nsd, buff, sizeof(buff));
    printf("MESSAGE FROM CLIENT : %s\n", buff);

    write(nsd, "ACK FROM SERVER\n", sizeof("ACK FROM SERVER\n"));

    close(sd);
}