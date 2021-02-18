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
			fgets(clientStr, 100, stdin);
			if(strcmp(clientStr, exit) == 0) {
				kill(child, SIGKILL);
				wait(NULL);
				break;
			}
			FILE *clientPipe = fopen(clientLoc, "w");			
			fprintf(clientPipe, "%s", clientStr);
			fclose(clientPipe);
		}
	}
	else {
		while(1) {
			FILE *serverPipe = fopen(serverLoc, "r");
			fgets(serverStr, 100, serverPipe);
			if(strlen(serverStr)) printf("Server Message : %s", serverStr);
			fclose(serverPipe);
		}
	}
	return 0;
}