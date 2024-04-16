#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    // Open the FIFO for reading
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the FIFO
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the string
    buffer[bytes_read] = '\0';

    // Display the message received from the FIFO
    printf("Message received from FIFO: %s\n", buffer);

    // Close the FIFO
    close(fd);

    // Remove the FIFO (optional)
    unlink(FIFO_PATH);

    return 0;
}
