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
    int fifo_read, fifo_write;

    while (flag == 0) {
        fifo_read = open("pipeA", O_RDONLY);
        if (fifo_read < 0)
            printf("\nCould not open pipeA");
        else if (!flag) {
            read(fifo_read, str, 255 * sizeof(char));
            close(fifo_read);
            if (strcmp(str, exit) == 0)
                printf("***** Client exited the chat *****\n");
            else
                printf("Client: %s\n", str);
        } else {
            close(fifo_read);
        }

        fifo_write = open("pipeB", O_WRONLY);
        if (fifo_write < 0)
            printf("\nCould not open pipeB");
        else
        {
            printf("You: ");
            fgets(str, 256, stdin);
            write(fifo_write, str, 255 * sizeof(char));
            close(fifo_write);
            if (strcmp(str, exit) == 0) flag = 1;
        }

        if(flag){
            close(fifo_write);
            close(fifo_read);
            return;
        }
    }
}