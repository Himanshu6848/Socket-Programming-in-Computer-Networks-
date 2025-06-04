#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct message {
    long mtype;
    char mtext[150];
};

int main() {
    int msgid, len = 150;
    key_t key = 131;
    struct message buff;

    msgid = msgget(key, IPC_CREAT | 0666);
    printf("msgid = %d\n", msgid);

    if (msgrcv(msgid, &buff, len, 0, 0) == -1) {
        perror("Message receive failed");
        exit(1);
    }

    printf("Message received: %s\n", buff.mtext);

    return 0;
}
