#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>



int main(int argc, char **argv) {
    int fd = open ("/tmp/servidor",O_WRONLY);
    char buffer[1024];
    buffer[0] = 0;
    for (int i = 1; i < argc; i++){
        strcat (buffer,argv[i]);
        if (i < argc -1)strcat (buffer," ");
    }
    strcat (buffer,"\n");
    write (fd,buffer,strlen (buffer) + 1);
    close (fd);
    
}