#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main (){
    if (!fork()){
        execlp ("ls","ls","-l",NULL);
    }
    _exit(0);
}