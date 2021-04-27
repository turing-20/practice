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
#include <sys/wait.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#define KEY_SIZE 10000

#define SA struct sockaddr

void signal_handler(int sig)
{
    exit(0);
}

void str_echo(int sockfd, RSA *rsa_public, RSA *rsa_private)
{
    int child;
    // int test = getpid();

    if (!(child = fork()))
    {
        signal(SIGUSR1, signal_handler);
        while (1)
        {
            char buff[80];
            bzero(buff, sizeof(buff));

            printf("Enter Data:>\n");
            fgets(buff, sizeof(buff), stdin);

            buff[strlen(buff) - 1] = '\0';

            char encrypted[RSA_size(rsa_public)];
            bzero(encrypted, sizeof(encrypted));

            int result;
            if ((result = RSA_public_encrypt((RSA_size(rsa_public) - 11), buff, encrypted, rsa_public, RSA_PKCS1_PADDING)) == -1)
            {
                printf("encryption failed\n");
            }
            if (strlen(encrypted) > 0)
            {
                write(sockfd, encrypted, RSA_size(rsa_public));
            }
            else
            {
                continue;
            }

            if (strcmp(buff, "exit") == 0)
            {

                // kill(getppid(), SIGUSR1);
                // exit(0);
                break;
            }
        }
        exit(0);
    }
    int child2;
    if (!(child2 = fork()))
    {
        while (1)
        {
            char buff[RSA_size(rsa_private)];
            bzero(buff, sizeof(buff));

            char encrypted[RSA_size(rsa_private)];
            bzero(encrypted, sizeof(encrypted));

            if (read(sockfd, encrypted, sizeof(encrypted)) <= 0)
                break;

            if (strlen(encrypted) > 0)
            {
                int result;
                if ((result = RSA_private_decrypt(RSA_size(rsa_private), encrypted, buff, rsa_private, RSA_PKCS1_PADDING)) == -1)
                {
                    printf("decryption failed %ld \n", strlen(encrypted));
                }
                if (strcmp(buff, "exit") == 0)
                {
                    // exit(EXIT_SUCCESS);
                    break;
                }

                printf("encrypted:\n%s \ndata received:\n%s\n", encrypted, buff);
                printf("Enter Data:>\n");
            }
            else
            {
                continue;
            }
        }
        exit(0);
    }
    wait(NULL);
    kill(child, SIGKILL);
    kill(child2, SIGKILL);
    return;
}

int main(int argc, char **argv)
{
    signal(SIGUSR1, signal_handler);
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

    RSA *rsa_public = RSA_new();
    FILE *fp_public = fopen(argv[4], "rb");
    rsa_public = PEM_read_RSA_PUBKEY(fp_public, &rsa_public, NULL, NULL);

    RSA *rsa_private = RSA_new();
    FILE *fp_private = fopen(argv[3], "rb");
    rsa_private = PEM_read_RSAPrivateKey(fp_private, &rsa_private, NULL, NULL);

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server unreachable\n");
        exit(0);
    }
    else
    {
        printf("Connection Successfull\n");
    }

    str_echo(sockfd, rsa_public, rsa_private);
    close(sockfd);
    return 0;
}