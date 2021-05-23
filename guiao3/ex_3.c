#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char**argv){
    for (int i = 0; i < argc;i++){
        printf ("argv[%d] = %s\n",i,argv[i]);
    }
}