#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sockfd, len, result;
    struct sockaddr_in address;
    int num;
    char response[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = 9001;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *) &address, len);

    if (result == -1) {
        perror("Unable to connect");
        exit(1);
    }

    printf("Enter the number: ");
    scanf("%d", &num);

    write(sockfd, &num, sizeof(num));
    read(sockfd, response, sizeof(response));

    printf("Palindrome check from server: %s\n", response);

    close(sockfd);
    return 0;
}
