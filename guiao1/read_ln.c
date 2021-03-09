#include <sys/types.h>
#include "read_ln.h"


ssize_t readln(int fd, char *line, size_t size){
    int i = 0;
    if (read(fd,line+i,size) <= 0) return 0;
    for (i = 0; i < size;i++)
        if (line[i] == '\n')break;
    line[++i] = 0;
    return (i == size ? 0 : i); 
}

/*
int main (int argc, char **argv){
    char *buffer = malloc (sizeof(char) * 20);
    int fd = open ("file",O_RDONLY);
    if (readln (fd,buffer,20)) printf("%s",buffer);
    free(buffer);
}
*/