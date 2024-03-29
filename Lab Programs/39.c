#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Create FIFO if not already exists
    mkfifo(FIFO_PATH, 0666);

    // Open FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize file descriptor set
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set timeout for select
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Wait for data to be written into FIFO within 10 seconds
    printf("Waiting for data...\n");
    int ready = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ready == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (ready == 0) {
        printf("No data available within 10 seconds.\n");
    } else {
        // Data is available to be read
        printf("Data available. Reading...\n");
        ssize_t num_bytes = read(fd, buffer, BUFFER_SIZE);
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Data read from FIFO: %s\n", buffer);
    }

    // Close FIFO
    close(fd);

    // Remove FIFO file
    unlink(FIFO_PATH);

    return 0;
}
