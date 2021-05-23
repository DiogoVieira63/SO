#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv){
    argv[argc] = NULL;
    execvp(argv[1],&(argv[1]));
}