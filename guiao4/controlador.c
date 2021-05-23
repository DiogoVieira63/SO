#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>



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
    while (!out){
        printf ("Command Line:");
        if (!fgets (str,sizeof(str),stdin))break;
        char *line;
        char *ret;
        int pid;
        line = strtok (str,"\n");
        int append = 0;
        if (line){
            if (!(pid = fork())){ 
                if ((ret = strstr (line,"2>"))){
                    line = strtok (line,"2>");
                    if (ret[2] == '>'){ret+= 2;append = 1;}
                    else ret++;
                    ret = strtok (ret + 1," ");
                    int error_fd;
                    if (!append) error_fd = open(ret, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    else error_fd = open(ret, O_WRONLY| O_APPEND | O_CREAT, 0644);
                    dup2 (error_fd,STDERR_FILENO);
                    close (error_fd);
                }          
                if ((ret = strchr (line,'<'))){
                    line = strtok (line,"<");
                    ret = strtok (ret + 1," ");
                    int input_fd = open(ret, O_RDONLY);
                    dup2 (input_fd,STDIN_FILENO);
                    close (input_fd);
                } 
                if ((ret = strchr (line,'>')) && ret[-1] != '2'){
                    line = strtok (line,">");
                    if (ret[1] == '>'){ret++;append = 1;}
                    ret = strtok (ret + 1," ");
                    int output_fd;
                    if (!append) output_fd = open(ret, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    else output_fd = open(ret, O_WRONLY| O_APPEND | O_CREAT, 0644);
                    dup2 (output_fd,STDOUT_FILENO);
                    close (output_fd);   
                }          
                if (my_system (line)== -1) out = 1;
                _exit (out);
            }
            else waitpid (pid,&out,0);
        }
    }
}