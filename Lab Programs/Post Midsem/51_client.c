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

    connect(sd, (struct sockaddr *)(&server), sizeof(server));

    getchar();
    write(sd, "HI SERVER\n", sizeof("HI SERVER\n"));
    read(sd, buff, sizeof(buff));
    printf("MESSAGE FROM SERVER: %s\n", buff);

    printf("Press [Enter] to exit.............\n");
    getchar();

    close(sd);
}