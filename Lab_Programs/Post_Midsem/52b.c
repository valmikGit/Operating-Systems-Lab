#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CONNECTIONS 10

void *handle_connection(void *sock_desc) {
    int client_socket = *((int *)sock_desc);
    char buffer[1024] = {0};
    ssize_t valread;

    valread = read(client_socket, buffer, 1024);
    printf("Received: %s\n", buffer);
    write(client_socket, "Server: message received\n", strlen("Server: message received\n"));

    close(client_socket);
    free(sock_desc);
    pthread_exit(NULL);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accepting incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        printf("New connection accepted\n");

        // Creating a new thread to handle the connection
        int *client_sock = malloc(1);
        *client_sock = new_socket;
        if (pthread_create(&thread_id, NULL, handle_connection, (void *)client_sock) < 0) {
            perror("could not create thread");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
