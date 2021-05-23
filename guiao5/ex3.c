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
        dup2 (mypipe[0],STDIN_FILENO);
        execlp ("wc","wc",NULL);
    }
    else {//PAI 
        close(mypipe[0]);
        char frase[30];
        int bytes = 0;
        while ((bytes = read(STDIN_FILENO,frase,30)) > 0)
            write (mypipe[1],frase,bytes);
        close (mypipe[1]);
    }
}
