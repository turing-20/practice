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
#include <signal.h>
#define SA struct sockaddr

void str_echo(int sockfd)
{
    char buff[100];
    bzero(buff, sizeof(buff));

    int rb = read(sockfd, buff, sizeof(buff));

    printf("Mesaage recieved from client: ");
    buff[rb] = '\0';
    for (int i = strlen(buff) - 1; i >= 0; i--)
    {
        printf("%c", buff[i]);
    }
    printf("\n");

    bzero(buff, sizeof(buff));

    printf("Enter message to sent to client: \n");

    fgets(buff, sizeof(buff), stdin);

    write(sockfd, buff, strlen(buff));

    return;
}

int main(int argc, char **argv)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    pid_t childpid;

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
    // printf("Enter exit to stop server:\n");
    for (;;)
    {
        connfd = accept(sockfd, (SA *)&cli, &len);

        if ((childpid = fork()) == 0)
        {
            close(sockfd);
            str_echo(connfd);
            close(connfd);
            exit(EXIT_SUCCESS);
        }
        // str_echo(connfd);
    }
    close(sockfd);
    return 0;
}