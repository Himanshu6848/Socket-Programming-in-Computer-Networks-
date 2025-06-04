#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

int main() {
    int serv_sockfd, serv_len, num, original, rem, sum = 0, digits = 0;
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
    recvfrom(serv_sockfd, &num, sizeof(num), 0, (struct sockaddr *) &cli_address, &cli_len);

    printf("Received number from client: %d\n", num);

    original = num;
    int temp = num;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        rem = temp % 10;
        sum += pow(rem, digits);
        temp /= 10;
    }

    if (sum == original)
        strcpy(res, "Armstrong Number");
    else
        strcpy(res, "Not an Armstrong Number");

    sendto(serv_sockfd, res, sizeof(res), 0, (struct sockaddr *) &cli_address, cli_len);

    close(serv_sockfd);
    return 0;
}
