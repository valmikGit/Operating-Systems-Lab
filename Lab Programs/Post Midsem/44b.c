#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a key for the message queue
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    if ((msgid = msgget(key, 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive message from message queue with IPC_NOWAIT flag
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available in the queue.\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received message from message queue:\n");
        printf("Type: %ld\n", message.msg_type);
        printf("Text: %s\n", message.msg_text);
    }

    return 0;
}