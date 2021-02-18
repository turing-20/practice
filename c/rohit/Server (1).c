#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>

int main() {
	int child;
	char clientStr[100], serverStr[100], exit[6]={'e','x','i','t','\n','\0'};
	char *clientLoc = "/tmp/clientPipe", *serverLoc = "/tmp/serverPipe";
	mkfifo(clientLoc, 0666);
	mkfifo(serverLoc, 0666);
	if(child = fork()) {
		while(1) {
			fgets(serverStr, 100, stdin);
			if(strcmp(serverStr, exit) == 0) {
				kill(child, SIGKILL);
				wait(NULL);
				break;
			}
			FILE *serverPipe = fopen(serverLoc, "w");
			fprintf(serverPipe, "%s", serverStr);
			fclose(serverPipe);
		}
	}
	else {
		while(1) {
			FILE *clientPipe = fopen(clientLoc, "r");
			fgets(clientStr, 100, clientPipe);
			if(strlen(clientStr)) printf("Client Message : %s", clientStr);
			fclose(clientPipe);
		}
	}
	return 0;
}