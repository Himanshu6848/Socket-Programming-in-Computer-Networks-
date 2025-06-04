#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int serv_sockfd, cli_sockfd, serv_len, cli_len;
    struct sockaddr_in serv_address, cli_address;
    int n, a, b, c, i;
    char result[1000], term[20]; // The term array is a temporary buffer to store each individual Fibonacci number as a string before appending it to the full result string (result).

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

        a = 0;
        b = 1;
        result[0] = '\0'; // clear the result buffer

        for (i = 0; i < n; i++) {
            sprintf(term, "%d ", a);
            strcat(result, term);
            c = a + b;
            a = b;
            b = c;
        }

        printf("Sending Fibonacci series to client: %s\n", result);
        write(cli_sockfd, result, sizeof(result));

        close(cli_sockfd);
    }

    return 0;
}
