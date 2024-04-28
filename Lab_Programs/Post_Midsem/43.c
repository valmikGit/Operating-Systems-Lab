// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/ipc.h>
// #include <sys/msg.h>
// #include <string.h>

// #define MAX_MSG_SIZE 256

// struct msg_buffer {
//     long msg_type;
//     char msg_text[MAX_MSG_SIZE];
// };

// int main() {
//     key_t key;
//     int msgid;
//     struct msg_buffer message;

//     // Generate a key for the message queue
//     if ((key = ftok("/tmp", 'A')) == -1) {
//         perror("ftok");
//         exit(EXIT_FAILURE);
//     }

//     // Get the message queue ID
//     if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
//         perror("msgget");
//         exit(EXIT_FAILURE);
//     }

//     // Prompt user to enter message type and text
//     printf("Enter message type: ");
//     scanf("%ld", &message.msg_type);
//     getchar(); // Clear newline from input buffer

//     printf("Enter message text: ");
//     fgets(message.msg_text, MAX_MSG_SIZE, stdin);

//     // Remove newline character from message text
//     size_t len = strlen(message.msg_text);
//     if (message.msg_text[len - 1] == '\n')
//         message.msg_text[len - 1] = '\0';

//     // Send message to message queue
//     if (msgsnd(msgid, &message, strlen(message.msg_text) + 1, 0) == -1) {
//         perror("msgsnd");
//         exit(EXIT_FAILURE);
//     }

//     printf("Message sent to message queue.\n");

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main(){
    int msgid;

    key_t key;
    key=ftok(".",'a');
    msgid=msgget(key,IPC_CREAT|0644);
    struct msg_buffer buf;
    buf.msg_type=1L;

    strcpy(buf.msg_text,"hello");
    printf("%s\n",buf.msg_text);

    msgsnd(msgid,&buf,strlen(buf.msg_text)+1,0);

}