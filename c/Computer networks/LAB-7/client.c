#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <openssl/bio.h>
#include <time.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#define SA struct sockaddr

void parse_url(char *url, char **hostname, char **port, char **path)
{
    printf("URL: %s\n", url);

    char *p;
    p = strstr(url, "://");

    char *protocol = 0;
    if (p)
    {
        protocol = url;
        *p = 0;
        p += 3;
    }
    else
    {
        p = url;
    }

    if (protocol)
    {
        if (strcmp(protocol, "http"))
        {
            fprintf(stderr,
                    "Unknown protocol '%s'. Only 'http' is supported.\n",
                    protocol);
            exit(1);
        }
    }

    *hostname = p;
    while (*p && *p != ':' && *p != '/' && *p != '#')
        ++p;

    *port = "80";
    if (*p == ':')
    {
        *p++ = 0;
        *port = p;
    }
    while (*p && *p != '/' && *p != '#')
        ++p;

    *path = p;
    if (*p == '/')
    {
        *path = p + 1;
    }
    *p = 0;

    while (*p && *p != '#')
        ++p;
    if (*p == '#')
        *p = 0;

    printf("hostname: %s\n", *hostname);
    printf("port: %s\n", *port);
    printf("path: %s\n", *path);
}

int main(int argc, char **argv)
{
    char *url = argv[1];
    char *hostname, *port, *path;
    parse_url(url, &hostname, &port, &path);
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

    hostent = gethostbyname(hostname);

    servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*(hostent->h_addr_list)));
    servaddr.sin_port = htons(atoi(port));

    // printf("%d \n",servaddr.sin_addr.s_addr);
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server unreachable\n");
        exit(0);
    }
    else
    {
        printf("Connection Started\n");
    }

    // str_echo(sockfd);
    char buffer[2048];

    sprintf(buffer, "GET /%s HTTP/1.1\r\n", path);
    sprintf(buffer + strlen(buffer), "Host: %s:%s\r\n", hostname, port);
    sprintf(buffer + strlen(buffer), "Connection: close\r\n");
    sprintf(buffer + strlen(buffer), "User-Agent: honpwc web_get 1.0\r\n");
    sprintf(buffer + strlen(buffer), "\r\n");

    send(sockfd, buffer, strlen(buffer), 0);
    // printf("Sent Headers:\n%s", buffer);

    int bytes_received;

    bzero(&buffer, sizeof(buffer));

    recv(sockfd, buffer, sizeof(buffer), 0);

    // printf("%s\n",buffer);
    bzero(&buffer, sizeof(buffer));
    int bytes = 0;

    FILE *fp;
    if (strlen(path) > 2)
    {
        fp = fopen(path, "wb");
    }
    else
    {
        fp = fopen("test", "wb");
    }

    printf("Saving data...\n\n");

    while (bytes_received = recv(sockfd, buffer, sizeof(buffer), 0))
    {
        if (bytes_received == -1)
        {
            perror("recieve");
            exit(3);
        }
        fwrite(buffer, 1, bytes_received, fp);
        bytes += bytes_received;
    }

    fclose(fp);
    close(sockfd);
    return 0;
}