#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


//PAI PARA FILHO
int main() {
    pid_t pid;
    int mypipe[2];// {read,write}qqzq

    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
	
    if (!fork()) {//FILHO
        close(mypipe[1]);
        char toRead[10];
        int bytes = 0;
        while((bytes = read (mypipe[0],toRead,10)) > 0)
            write(STDOUT_FILENO, toRead, bytes);
        _exit (0);
    }
    else {//PAI 
        close(mypipe[0]);
        char *frase = "Hello World";
        write (mypipe[1],frase,strlen (frase));
        close (mypipe[1]);
        wait(NULL);
    }
}
