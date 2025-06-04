#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int serv_sockfd, serv_len, n, t1 = 0, t2 = 1, next;
    char res[200];
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

    printf("Received number of terms: %d\n", n);

    strcpy(res, "");
    for (int i = 1; i <= n; i++) {
        char temp[20];
        sprintf(temp, "%d ", t1);
        strcat(res, temp);
        next = t1 + t2;
        t1 = t2;
        t2 = next;
    }

    sendto(serv_sockfd, res, sizeof(res), 0, (struct sockaddr *) &cli_address, cli_len);

    close(serv_sockfd);
    return 0;
}
