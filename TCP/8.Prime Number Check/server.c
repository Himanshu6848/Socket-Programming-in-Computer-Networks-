#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int serv_sockfd, cli_sockfd, serv_len, cli_len;
    struct sockaddr_in serv_address, cli_address;
    int n, i, is_prime;
    char res[100];

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

        read(cli_sockfd, &n, sizeof(n));
        printf("Received number from client: %d\n", n);

        if (n <= 1) {
            strcpy(res, "Not Prime");
        } else {
            is_prime = 1;
            for (i = 2; i <= n / 2; i++) {
                if (n % i == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime)
                strcpy(res, "Prime");
            else
                strcpy(res, "Not Prime");
        }

        printf("Sending result to client: %s\n", res);
        write(cli_sockfd, res, sizeof(res));

        close(cli_sockfd);
    }

    return 0;
}
