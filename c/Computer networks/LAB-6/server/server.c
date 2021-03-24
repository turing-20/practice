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
#include <sys/shm.h>
#define SA struct sockaddr

int shmidconnections;

void str_echo(int sockfd)
{
    for (;;)
    {
        char buff[100];
        bzero(buff, sizeof(buff));

        int rb = read(sockfd, buff, sizeof(buff));

        if (rb <= 1)
        {
            printf("Client exited\n");
            return;
        }
        printf("Message recieved from client: ");
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
    }
}

int main(int argc, char **argv)
{

    shmidconnections = shmget(IPC_PRIVATE, 1 * sizeof(int), 0666 | IPC_CREAT);
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

    if ((listen(sockfd, 4)) != 0)
    {
        printf("Listen failed");
        exit(0);
    }
    else
    {
        printf("Listen successfull\n");
    }

    len = sizeof(cli);

    int *connections = (int *)shmat(shmidconnections, 0, 0);
    connections[0] = 0;

    for (;;)
    {
        connfd = accept(sockfd, (SA *)&cli, &len);
        connections[0] += 1;
        if ((childpid = fork()) == 0)
        {
            int *connections1 = (int *)shmat(shmidconnections, 0, 0);
            if (connections1[0] > 4)
            {
                printf("4 Clients Already Connected !\n");
                close(sockfd);
                char buff[100];
                bzero(buff, sizeof(buff));
                strcpy(buff, "Number of clients is 4 try again later");
                write(connfd, buff, strlen(buff));
                connections1[0]--;
                exit(0);
            }
            else
            {
                printf("Client Connected Port: %d\n", cli.sin_port);
                close(sockfd);
                char buff[100];
                bzero(buff, sizeof(buff));
                strcpy(buff, "Server Connected");
                write(connfd, buff, strlen(buff));
                str_echo(connfd);
                connections1[0]--;
                exit(0);
            }
            shmdt(connections1);
        }
        close(connfd);
    }

    shmdt(connections);
    shmctl(shmidconnections, IPC_RMID, NULL);

    close(sockfd);

    return 0;
}