#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int serv_sockfd, serv_len;
    struct sockaddr_in serv_address, cli_address;
    char a[100], b[100];

    serv_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9055;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *) &serv_address, serv_len);

    printf("Server is waiting...\n");

    socklen_t cli_len = sizeof(cli_address);
    recvfrom(serv_sockfd, a, sizeof(a), 0, (struct sockaddr *) &cli_address, &cli_len);

    printf("Message from the client: ");
    puts(a);

    getchar(); // to consume newline
    printf("Message from the server: ");
    scanf("%[^\n]s", b);

    sendto(serv_sockfd, b, sizeof(b), 0, (struct sockaddr *) &cli_address, cli_len);

    close(serv_sockfd);
    return 0;
}
