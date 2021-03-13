#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#define SA struct sockaddr



void str_echo(int sockfd)
{
    char buff[100];
    bzero(buff,sizeof(buff));

    printf("Enter Message to be sent to server:\n");

    fflush(stdin);
    fflush(stdout);

    scanf("%[^n]s",buff);
    write(sockfd,buff,sizeof(buff));

    bzero(buff,sizeof(buff));

    read(sockfd,buff,sizeof(buff));

    printf("Message received from server: %s",buff);

    return;
}

int main(int argc, char **argv)
{
    int sockfd, connfd;
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

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server unreachable\n");
        exit(0);
    }
    else
    {
        printf("Connection Successfull\n");
    }

    printf("Enter Message to be sent:\n");
    str_echo(sockfd);

    close(sockfd);
    return 0;
}