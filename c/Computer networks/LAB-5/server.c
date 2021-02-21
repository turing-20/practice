#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SA struct sockaddr

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        printf("Socket creation failed");
        exit(0);
    }
    else
    {
        printf("scoket created successfully \n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    servaddr.sin_port = htons(8080);

    if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Socket failed to bind");
        exit(0);
    }
    else
    {
        printf("Socket binded successfully\n");
    }

    if ((listen(sockfd, 10)) != 0)
    {
        printf("Listen failed");
        exit(0);
    }
    else
    {
        printf("Listen successfull\n");
    }

    len = sizeof(cli);

    connfd = accept(sockfd, (SA *)&cli, &len);

    if (connfd < 0)
    {
        printf("Server connection failed");
        exit(0);
    }
    else
    {
        printf("Connection established\n");
    }
    char buff[80];
    strcpy(buff, "HELLO WORLD");
    write(sockfd, buff, sizeof(buff));
    close(sockfd);

    return 0;
}