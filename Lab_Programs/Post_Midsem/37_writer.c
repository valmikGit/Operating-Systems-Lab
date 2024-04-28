#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    // Create the FIFO (named pipe)
    mkfifo(FIFO_PATH, 0666);

    // Open the FIFO for writing
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data to the FIFO
    char message[] = "Hello, FIFO!";
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the FIFO
    close(fd);

    return 0;
}
