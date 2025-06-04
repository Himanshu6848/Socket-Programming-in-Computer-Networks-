#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    int serv_sockfd, cli_sockfd, serv_len, cli_len;
    struct sockaddr_in serv_address, cli_address;
    char str[200], rev[100];
    int len, i;

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

        read(cli_sockfd, str, sizeof(str));
        printf("Reading message from client: %s\n", str);

        len = strlen(str);
        for (i = 0; i < len; i++) {
            rev[i] = str[len - i - 1];
        }
        rev[len] = '\0';

        printf("Reversing the string received from the client: %s\n", rev);

        write(cli_sockfd, rev, sizeof(rev));

        close(cli_sockfd);
    }

    return 0;
}
