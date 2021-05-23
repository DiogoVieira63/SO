#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv){
    for (int i = 1; i < argc;i++){
        if (!fork)
            execlp(argv[i], argv[i], NULL);
    }
    for (int i = 1; 1 < argc;i++)
        wait (NULL);

        
}