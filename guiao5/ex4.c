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
	
    if (!fork()) {//FILHO - LEITURA
        close(mypipe[1]);
        dup2 (mypipe[0],STDIN_FILENO);
        execlp ("wc","wc","-l",NULL);
    }
    else {//PAI - ESCRITA
        close(mypipe[0]);
        dup2(mypipe[1],STDOUT_FILENO);
        execlp ("ls","ls","/etc",NULL);
        close (mypipe[1]);
    }
}
