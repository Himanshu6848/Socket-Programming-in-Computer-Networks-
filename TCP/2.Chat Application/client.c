#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    int sockfd, len, result;
    struct sockaddr_in address;
    char name[100], ser[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons9005;
    address.sin_addr.s_addr = inet_addr("127.0.0.2");

    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *) &address, len);

    if (result == -1) {
        perror("Unable to connect");
        exit(1);
    }

    for (;;) {
        getchar();
        printf("Enter the message: ");
        scanf("%[^\n]s", name);  
        write(sockfd, name, sizeof(name));

        read(sockfd, ser, sizeof(ser));

        printf("Reading from server:\n");
        puts(ser);
    }

    close(sockfd);
    return 0;
}
