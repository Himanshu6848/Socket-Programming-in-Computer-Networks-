#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sockfd, len, result;
    struct sockaddr_in address;
    int n;
    char res[100];

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
    scanf("%d", &n);

    write(sockfd, &n, sizeof(n));
    read(sockfd, res, sizeof(res));

    printf("Result from server: %s\n", res);

    close(sockfd);
    return 0;
}
