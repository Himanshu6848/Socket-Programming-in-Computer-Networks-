#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int serv_sockfd, cli_sockfd, serv_len, cli_len;
    struct sockaddr_in serv_address, cli_address;
    int num, temp, rev, digit;
    char result[100];

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9001;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *) &serv_address, serv_len);
    listen(serv_sockfd, 5);

    while (1) {
        printf("Server is waiting...\n");

        cli_len = sizeof(cli_address);
        cli_sockfd = accept(serv_sockfd, (struct sockaddr *) &cli_address, &cli_len);

        read(cli_sockfd, &num, sizeof(num));
        printf("Reading number from client: %d\n", num);

        temp = num;
        rev = 0;

        while (temp != 0) {
            digit = temp % 10;
            rev = rev * 10 + digit;
            temp = temp / 10;
        }

        if (rev == num) {
            strcpy(result, "Yes");
        } else {
            strcpy(result, "No");
        }

        printf("Sending palindrome result to client: %s\n", result);
        write(cli_sockfd, result, sizeof(result));

        close(cli_sockfd);
    }

    return 0;
}
