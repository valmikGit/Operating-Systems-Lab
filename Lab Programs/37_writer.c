#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char *message = "Hello, FIFO!";

    // Create FIFO file
    mkfifo(FIFO_FILE, 0666);

    // Open FIFO for writing
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write message to FIFO
    write(fd, message, strlen(message) + 1);
    close(fd);

    printf("Data written to FIFO successfully.\n");

    return 0;
}
