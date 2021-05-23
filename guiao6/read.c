#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>


int main() {
    int fd = open ("/tmp/fifo",O_WRONLY);
    char buffer[100];
    while (1)
    {
        int bytes;
        if (( bytes = read (STDIN_FILENO,buffer,100)) == 0) break;
        write (fd,buffer,bytes);
    }
    close (fd);
    unlink ("/tmp/fifo");
}
