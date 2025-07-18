#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int serv_sockfd, serv_len, n, i, isPrime = 1;
    char res[100];
    struct sockaddr_in serv_address, cli_address;

    serv_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9055;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *) &serv_address, serv_len);

    printf("Server is waiting...\n");

    socklen_t cli_len = sizeof(cli_address);
    recvfrom(serv_sockfd, &n, sizeof(n), 0, (struct sockaddr *) &cli_address, &cli_len);

    printf("Received number: %d\n", n);

    if (n <= 1) {
        strcpy(res, "Not Prime");
    } else {
        for (i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
            strcpy(res, "Prime");
        else
            strcpy(res, "Not Prime");
    }

    sendto(serv_sockfd, res, sizeof(res), 0, (struct sockaddr *) &cli_address, cli_len);

    close(serv_sockfd);
    return 0;
}
