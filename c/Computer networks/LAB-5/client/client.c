#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SA struct sockaddr



void str_echo(int sockfd)
{
    for(;;)
    {
        char buff[80];
        bzero(buff,sizeof(buff));


        scanf("%s",buff);

        if(strncmp("exit",buff,4)==0)
        {
            printf("Client Exit\n");
            break;
        }

        FILE* f;

        f=fopen(buff,"w");

        write(sockfd,buff,sizeof(buff));

        bzero(buff,sizeof(buff));
        
        read(sockfd,buff,sizeof(buff));
        fprintf(f,"%s",buff);

        printf("File recieved\n");
        fclose(f);
    }

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
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server unreachable\n");
        exit(0);
    }
    else
    {
        printf("Connection Successfull\n");
    }

    str_echo(sockfd);

    close(sockfd);
    return 0;
}