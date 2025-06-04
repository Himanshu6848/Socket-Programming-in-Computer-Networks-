#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd, len;
    struct sockaddr_in serv_addr;
    char str[200], rev[200];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(serv_addr);

    printf("Enter the string: ");
    scanf(" %[^\n]", str);

    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *) &serv_addr, len);

    recvfrom(sockfd, rev, sizeof(rev), 0, NULL, NULL);

    printf("Reversed string from server: %s\n", rev);

    close(sockfd);
    return 0;
}
