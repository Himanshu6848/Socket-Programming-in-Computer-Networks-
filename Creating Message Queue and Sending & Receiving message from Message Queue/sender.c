#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct message {
    long mtype;
    char mtext[150];
};

int main() {
    int msgid, len;
    struct message msg;
    key_t key = 131;

    msgid = msgget(key, IPC_CREAT | 0666);
    if(msgid == -1){
            perror("msgget failed");
            exit(1);
    }
    printf("msgid = %d\n", msgid);

    printf("Enter the message: ");
    scanf("%s", msg.mtext);

    msg.mtype = 1;
    len = strlen(msg.mtext) + 1;

    if (msgsnd(msgid, &msg, len, 0) == -1) {
        perror("msgsnd error");
        exit(1);
    }
    printf("Message sent\n");

    return 0;
}
