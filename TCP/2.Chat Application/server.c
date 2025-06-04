#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    int serv_sockfd, cli_sockfd;
    int serv_len, cli_len;
    struct sockaddr_in serv_address, cli_address;
    char a[200], b[100];

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9005;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *) &serv_address, serv_len);

    listen(serv_sockfd, 5);

    while (1) {
        printf("Server is waiting...\n");
        cli_len = sizeof(cli_address);
        cli_sockfd = accept(serv_sockfd, (struct sockaddr *) &cli_address, &cli_len);

        for (;;) {
            read(cli_sockfd, a, sizeof(a));
            printf("Reading message from client...\n");
            puts(a);

            printf("Enter the message for the client: ");
            scanf("%[^\n]s", b);

            write(cli_sockfd, b, sizeof(b));
        }

        close(cli_sockfd);
    }

    return 0;
}
