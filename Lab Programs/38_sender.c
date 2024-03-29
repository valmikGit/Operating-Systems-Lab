#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define FIFO_SENDER "sender_fifo"
#define FIFO_RECEIVER "receiver_fifo"
#define BUFFER_SIZE 256

int main() {
    int sender_fd, receiver_fd;
    char sender_buffer[BUFFER_SIZE];
    char receiver_buffer[BUFFER_SIZE];

    // Create FIFO files
    mkfifo(FIFO_SENDER, 0666);
    mkfifo(FIFO_RECEIVER, 0666);

    // Open FIFO for writing
    sender_fd = open(FIFO_SENDER, O_WRONLY);
    if (sender_fd == -1) {
        perror("open sender_fifo");
        exit(EXIT_FAILURE);
    }

    // Open FIFO for reading
    receiver_fd = open(FIFO_RECEIVER, O_RDONLY);
    if (receiver_fd == -1) {
        perror("open receiver_fifo");
        exit(EXIT_FAILURE);
    }

    // Write message to FIFO
    strcpy(sender_buffer, "Hello, FIFO receiver!");
    write(sender_fd, sender_buffer, strlen(sender_buffer) + 1);

    // Read response from FIFO
    read(receiver_fd, receiver_buffer, BUFFER_SIZE);
    printf("Received response from FIFO receiver: %s\n", receiver_buffer);

    // Close FIFOs
    close(sender_fd);
    close(receiver_fd);

    // Remove FIFO files
    unlink(FIFO_SENDER);
    unlink(FIFO_RECEIVER);

    return 0;
}
