#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#define KEY_SIZE 10000

#define SA struct sockaddr

void str_echo(int sockfd0, int sockfd1)
{
    if (!fork())
    {
        while (1)
        {
            char buff[1024];
            bzero(buff, sizeof(buff));
            if (read(sockfd0, buff, sizeof(buff)) <= 0)
            {
                exit(0);
            }
            write(sockfd1, buff, sizeof(buff));
        }
    }
    else
    {
        while (1)
        {
            char buff[1024];
            bzero(buff, sizeof(buff));
            if (read(sockfd1, buff, sizeof(buff)) <= 0)
            {
                break;
            }
            write(sockfd0, buff, sizeof(buff));
        }
    }
    // wait(NULL);
}

int main(int argc, char **argv)
{
    int sockfd, connfd0, connfd1, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        printf("Socket creation failed");
        exit(0);
    }
    else
    {
        printf("socket created successfully \n");
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));
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
    while (1)
    {
        printf("Waiting for new connections\n");

        connfd0 = accept(sockfd, (SA *)&cli, &len);
        printf("Client connected\n");
        connfd1 = accept(sockfd, (SA *)&cli, &len);
        printf("Client connected\n");
        str_echo(connfd0, connfd1);

        close(connfd0);
        close(connfd1);
    }
    close(sockfd);
}