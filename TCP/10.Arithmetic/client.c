#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct calc {
    int num1;
    int num2;
    char op;
};

int main() {
    int sockfd, len, result;
    struct sockaddr_in address;
    struct calc c;
    char res[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = 9055;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *) &address, len);
    if (result == -1) {
        perror("Unable to connect");
        exit(1);
    }

    printf("Enter first number: ");
    scanf("%d", &c.num1);
    printf("Enter second number: ");
    scanf("%d", &c.num2);
    getchar(); // consume leftover newline
    printf("Enter operator (+, -, *, /): ");
    scanf("%c", &c.op);

    write(sockfd, &c, sizeof(c));
    read(sockfd, res, sizeof(res));

    printf("Result received from server: %s\n", res);

    close(sockfd);
    return 0;
}
