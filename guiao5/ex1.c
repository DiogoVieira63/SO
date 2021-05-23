#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


//PAI PARA FILHO
/*
int main() {
    pid_t pid;
    int mypipe[2];// {read,write}qqzq

    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
	
    if (!fork()) {//FILHO
        close(mypipe[1]);
        char toRead[20];
        int bytes = read (mypipe[0],toRead,20);
        close (mypipe[0]);
        write(STDOUT_FILENO, toRead, bytes);
        _exit (0);
    }
    else {//PAI 
        close(mypipe[0]);
        char *frase = "Hello World";
        sleep (5);
        write (mypipe[1],frase,strlen (frase));
        wait(NULL);
    }
}
*/
//FILHO PARA PAI
int main() {
    pid_t pid;
    int mypipe[2];// {read,write}qqzq

    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
	
    if (!fork()) {//FILHO WRITE
        close(mypipe[0]);
        char *frase = "Hello World";
        write (mypipe[1],frase,strlen (frase));
    }
    else {//PAI READ
        close(mypipe[1]);
        char toRead[20];
        int bytes = read (mypipe[0],toRead,20);
        write(STDOUT_FILENO, toRead, bytes);
    }
}
