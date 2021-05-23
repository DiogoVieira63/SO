#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

static int out = 0;

void ctrlChandler (int signum){
    printf ("\nEXIT\n");
    out = 1;
}


int main() {
    //criação do pipe com nome
    mkfifo ("/tmp/servidor",0644);
    int fd = open ("/tmp/servidor",O_RDONLY);
    char buffer[100];
    while (!out){
        int bytes;
        if (signal (SIGINT,ctrlChandler) == SIG_ERR)
            perror ("SIGINT ERROR\n");
        while ((bytes = read (fd,buffer,100)) != 0)
        {
            int log_fd = open ("log.txt",O_WRONLY | O_CREAT |O_APPEND,0400);
            if (log_fd == -1)printf ("Erro na leitura/criação do ficheiro logs\n");
            else
            {
            write (log_fd,buffer,bytes);
            close (log_fd);
            }
           }
    }
    close (fd);
    unlink ("/tmp/servidor");
    
}