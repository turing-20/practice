#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int child;

    char clientmessage[100];
    char servermesaage[100];
    char exit[6] = {'e', 'x', 'i', 't', '\n', '\0'};

    char *clientfifo = "/tmp/clientnamedpipe";
    char *serverfifo = "/tmp/servernamedpipe";

    mkfifo(clientfifo, 0666);
    mkfifo(serverfifo, 0666);

    if (child = fork())
    {
        while (1)
        {
            fgets(servermesaage, 100, stdin);

            if (strcmp(servermesaage, exit) == 0)
            {
                kill(child, SIGKILL);
                wait(NULL);
                break;
            }

            FILE *servernamedpipe = fopen(serverfifo, "w");

            fprintf(servernamedpipe, "%s", servermesaage);
            fclose(servernamedpipe);
        }
    }
    else
    {
        while (1)
        {
            FILE *clientnamedpipe = fopen(clientfifo, "r");
            fgets(clientmessage, 100, clientnamedpipe);

            if (strlen(clientmessage))
                printf("Client Message : %s", clientmessage);

            fclose(clientnamedpipe);
        }
    }
    return 0;
}