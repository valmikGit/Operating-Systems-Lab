#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO file created successfully.\n");
    return 0;
}
