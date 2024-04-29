// to demonstrate: run server on one terminal
// open 2 more terminals, run 'nc localhost 8080', enter followed by a message in both
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[200];

    ssize_t bytes_received = recv(client_socket, buffer, 200, 0);
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        pthread_exit(NULL);
    }
    buffer[bytes_received] = '\0';

    printf("Received message from client: %s\n", buffer);
    printf("Closing thread...");
    close(client_socket);
    pthread_exit(NULL);
}


int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[200];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("Server listening on port %d...\n", 8080);

    while (1) {
        client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, &client_socket);
    }

    close(server_socket);

    return 0;
}