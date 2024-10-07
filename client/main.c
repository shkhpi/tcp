#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main (int argc, char **argv)
{
    if (argc < 2) {
        printf("Input arguments missing!\n");
        exit(1);        
    }

    struct sockaddr_in serveraddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[ Socket ]");
        exit(-1);
    }
    printf("Socket successfully created!\n");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
         perror("[ Connect ]");
         exit(-2);
    }
    printf("Connection established successfully!\n");

    char buff[64] = "Hello from the client side!\n";
    write(sockfd, buff, strlen(buff));

    memset(buff, 0, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("Server msg:\n\n%s\n", buff);

    close(sockfd);

    return 0;
}