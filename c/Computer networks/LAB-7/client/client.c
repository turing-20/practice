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
    
}

int main(int argc, char **argv)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    struct hostent *hostent;
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
    

    hostent = gethostbyname("example.com");

    servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
    servaddr.sin_port = htons(80);

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server unreachable\n");
        exit(0);
    }
    else
    {
        printf("Connection Started\n");
    }

    str_echo(sockfd);

    close(sockfd);
    return 0;
}