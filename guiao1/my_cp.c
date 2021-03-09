#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int size (int f){
    int size = lseek(f, 0, SEEK_END); 
    lseek(f, 0, SEEK_SET);
    return size;
}


int main (int argc, char **argv){
    int fp = open ("example.txt",O_RDONLY);
    //int file_size = size (fp);
    int fd = open ("example_copy.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    char *buffer = malloc (sizeof (char) * 2048);
    //read all at once 
    //read (fp,buffer,  file_size*sizeof(char));
    //write (fd, buffer,file_size*sizeof(char));
    //read in blocks
    int buffer_size = 2048;
    int bytes_read = 0; 
    int bytes_write = 0; 
    char *block_buffer = malloc (sizeof (char) * buffer_size);
    while ((bytes_read = read(fp,block_buffer, buffer_size)) > 0)
    {
        bytes_write += write(fd,block_buffer,bytes_read);
    }
    close(fp);
    close (fd);
    free (buffer);
    free (block_buffer);
    
}