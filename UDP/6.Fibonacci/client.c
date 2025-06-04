#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd, len, n;
    char res[200];
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = 9055;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    printf("Enter number of terms: ");
    scanf("%d", &n);

    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *) &address, len);

    recvfrom(sockfd, res, sizeof(res), 0, (struct sockaddr *) &address, &len);

    printf("Fibonacci Series from Server: %s\n", res);

    close(sockfd);
    return 0;
}
