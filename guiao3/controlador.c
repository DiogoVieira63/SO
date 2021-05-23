#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>



int my_system (char *line){
    int result;
    char *index;
    int need_wait = 1; 
    int status, pid;
    if ((index = strchr (line,'&'))) {
        need_wait = 0;
        index[0] = 0;
    }
    if (!strcmp (line,"exit")) return -1;
    char *words [1024];
    int i = 0;
    char* token;
    char* rest = line;
    while ((token = strtok_r(rest, " ", &rest)))
        words[i++] = token;
    if (!(pid = fork())){
        words[i] = NULL;
        result = execvp(words[0],words);
    }
    else
        if (need_wait) waitpid (pid,&status,0);
    return WEXITSTATUS(status);
}




int main (){
    char str[1024];
    int out = 0;
    while (1){
        printf ("Command Line:");
        if (!fgets (str,sizeof(str),stdin))break;
        char *line;
        line = strtok (str,"\n");
        if (line)
            if (my_system (line)== -1) break;
    }
}