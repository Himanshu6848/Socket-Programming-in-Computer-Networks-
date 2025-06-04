#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd, len, num, rev;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = 9055;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    printf("Enter the number: ");
    scanf("%d", &num);

    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr *) &address, len);

    recvfrom(sockfd, &rev, sizeof(rev), 0, (struct sockaddr *) &address, &len);

    printf("Reversed number from server: %d\n", rev);

    close(sockfd);
    return 0;
}
