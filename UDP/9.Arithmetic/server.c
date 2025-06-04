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
    int serv_sockfd, serv_len;
    struct sockaddr_in serv_address, cli_address;
    struct calc c;
    char res[100];
    float result;

    serv_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = 9055;
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd, (struct sockaddr *) &serv_address, serv_len);

    printf("Server is waiting...\n");

    socklen_t cli_len = sizeof(cli_address);

    recvfrom(serv_sockfd, &c, sizeof(c), 0, (struct sockaddr *) &cli_address, &cli_len);

    printf("Received: %d %c %d\n", c.num1, c.op, c.num2);

    switch(c.op) {
        case '+': result = c.num1 + c.num2; break;
        case '-': result = c.num1 - c.num2; break;
        case '*': result = c.num1 * c.num2; break;
        case '/':
            if(c.num2 == 0)
                strcpy(res, "Division by zero error");
            else
                sprintf(res, "%.2f", (float)c.num1 / c.num2);
            break;
        default:
            strcpy(res, "Invalid operator");
    }

    if (c.op != '/' && c.op == '+' || c.op == '-' || c.op == '*')
        sprintf(res, "%.2f", result);

    sendto(serv_sockfd, res, sizeof(res), 0, (struct sockaddr *) &cli_address, cli_len);

    close(serv_sockfd);
    return 0;
}
