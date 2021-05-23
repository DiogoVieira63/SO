#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//TO BE DONE || NOT WORKING RIGHT

int main (int argc, char **argv){
    int pid, status;
    for (int i = 1; i < argc;i++){
        if (!(pid = fork())){   
            execlp (argv[i],argv[i],NULL);      
        }
    }
    for (int i = 1; 1 < argc;i++){
        // waitpid (pid,&status,0);
        wait(&status);
        printf ("%d\n",WEXITSTATUS(status));
    }

    return 0;
}