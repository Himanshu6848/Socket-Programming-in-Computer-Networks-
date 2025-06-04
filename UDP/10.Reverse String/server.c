#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd, len, n;
    struct sockaddr_in serv_addr, cli_addr;
    char str[200], rev[200];
    int i;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(serv_addr);

    bind(sockfd, (struct sockaddr *) &serv_addr, len);

    printf("Server is waiting...\n");

    len = sizeof(cli_addr);
    n = recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *) &cli_addr, &len);
    str[n] = '\0';  // Null terminate received string

    int length = strlen(str);
    for(i = 0; i < length; i++) {
        rev[i] = str[length - i - 1];
    }
    rev[length] = '\0';

    printf("Received string: %s\n", str);
    printf("Reversed string: %s\n", rev);

    sendto(sockfd, rev, sizeof(rev), 0, (struct sockaddr *) &cli_addr, len);

    close(sockfd);
    return 0;
}
