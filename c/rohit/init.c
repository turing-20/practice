#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {   
    int f1, f2;
    f1 = mkfifo("pipeA", 0666);
    if (f1 < 0) printf("\npipeA not created");
    else printf("\npipeA created");
    f2 = mkfifo("pipeB", 0666);
    if (f2 < 0) printf("\npipeB not created");
    else printf("\npipeB created\n");
    return 0;
}