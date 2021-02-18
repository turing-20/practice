#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int child;

    char clientmessage[100];
    char servermessage[100];
    char exit[6] = {'e', 'x', 'i', 't', '\n', '\0'};

    char *clientfifo = "/tmp/clientnamedpipe";
    char *serverfifo = "/tmp/servernamedpipe";

    mkfifo(clientfifo, 0666);
    mkfifo(serverfifo, 0666);

    if (child = fork())
    {
        while (1)
        {
            fgets(clientmessage, 100, stdin);

            if (strcmp(clientmessage, exit) == 0)
            {
                kill(child, SIGKILL);
                wait(NULL);
                break;
            }
            FILE *clientnamedpipe = fopen(clientfifo, "w");

            fprintf(clientnamedpipe, "%s", clientmessage);
            fclose(clientnamedpipe);
        }
    }
    else
    {
        while (1)
        {
            FILE *servernamedpipe = fopen(serverfifo, "r");

            fgets(servermessage, 100, servernamedpipe);
            if (strlen(servermessage))
                printf("Server Message : %s", servermessage);

            fclose(servernamedpipe);
        }
    }
    return 0;
}