#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        perror("socket");
        return 1;
    }
    printf("Socket created successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_addr.s_addr = INADDR_ANY, // Change here
        .sin_family = AF_INET,
        .sin_port = htons(8080)
    };

    int status = bind(sockfd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr));

    if (status == -1)
    {
        perror("bind");
        return 1;
    }
    
    printf("Socket binded successfully\n");

    int backlog = 5;
    status = listen(sockfd, backlog);

    if (status == -1)
    {
        perror("listen");
        return 1;
    }
    
    printf("Listening...\n");

    return 0;
}
