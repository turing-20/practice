#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void main() {

    char str[256] = "start";
    char exit[256] = "exit\n";
    int flag = 0;
    int fifo_write, fifo_read;

    while (flag == 0) {
        fifo_write = open("pipeA", O_WRONLY);
        if (fifo_write < 0)
            printf("\nCould not open pipeA");
        else
        {
            printf("You: ");
            fgets(str, 256, stdin);
            write(fifo_write, str, 255 * sizeof(char));
            close(fifo_write);
            if (strcmp(str, exit) == 0) flag = 1;
        }
        
        fifo_read = open("pipeB", O_RDONLY);
        if (fifo_read < 0)
            printf("\nCould not open pipeB");
        else if (!flag){
            read(fifo_read, str, 255 * sizeof(char));
            close(fifo_read);
            if (strcmp(str, exit) == 0){
                printf("***** Server exited the chat *****\n");
                continue;
            }
            else
                printf("Server: %s\n", str);
        }else{
            close(fifo_read);
        }

        if(flag){
            printf("Exiting...\n");
            return;
        }
    }
}