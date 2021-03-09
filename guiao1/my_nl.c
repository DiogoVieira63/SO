#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


ssize_t readln(int fd, char *line, size_t size){
    int i = 0;
    while (i < size)
    {
        read(fd,line+i,1);
        if (line[i++] == '\n')break;
    }
    line[i] = 0; 
}

int main (int argc, char **argv){
    char *buffer = malloc (sizeof(char) * 2048);
    int i = 1;
    while (1)
    {
        readln (STDIN_FILENO,buffer,2048);
        printf("\t%i %s",i++,buffer);
    }
    free(buffer);
}