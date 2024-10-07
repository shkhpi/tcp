#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6565

int main()
{
    struct sockaddr_in serveraddr, clinetaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[ Socket ]");
        exit(-1);
    }
    printf("Socket created successfully!\n");

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("[ Bind ]");
        exit(-2);
    }
    printf("Socket successfully binded!\n");

    printf("Waiting for client connection...\n");
    if(listen(sockfd, 1) < 0) {
        perror("[ Listen ]");
        exit(-3);
    }

    socklen_t len = sizeof(clinetaddr);
    int clientfd = accept(sockfd, (struct sockaddr *)&clinetaddr, &len);
    if (clientfd < 0) {
        perror("[ Accept ]");
        exit(-4);
    }   
    printf("Client %s connected successfully...\n", inet_ntoa(clinetaddr.sin_addr));

    char buff[1024] = {0};

    read(clientfd, buff, sizeof(buff));
    printf("Clinet msg:\n\n%s\n", buff);

    write(clientfd, "Hello", 5);

    close(sockfd);

    return 0;
}
