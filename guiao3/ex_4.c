#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>




int main (){
	char buffer[1024];
	char* args[1024];
    args[0] ="./ex_3";
    int i = 1;
    while (fgets (buffer,sizeof(buffer),stdin))
    {
        buffer [strlen (buffer) -1] = 0;
        args[i++] = strdup (buffer);
    }
	args[i] = NULL;
	execv("./ex_3", args);
    
}