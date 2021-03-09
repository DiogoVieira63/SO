#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv){
    int buffer_size = 2048;
    char *buffer = malloc (sizeof (char) * buffer_size);
    int read_bytes = 0; 
    while ((read_bytes = read(STDIN_FILENO, buffer, buffer_size)) > 0){
        write(STDOUT_FILENO,buffer,read_bytes);
    }
    free (buffer);
}