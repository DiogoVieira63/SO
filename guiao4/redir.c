#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main (int argc, char **argv){
    int command = 1;
    for (int i = 1; i <argc;i++){
        if (!strcmp (argv[i],"-i")){
            int input_fd = open (argv[i + 1],O_RDONLY);
            dup2 (input_fd,STDIN_FILENO);
            close (input_fd);
            command += 2;
        }
        if (!strcmp (argv[i],"-o")){
            int output_fd = open(argv[i +1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2 (output_fd,STDOUT_FILENO);
            close (output_fd);
            command += 2;
        }
    }
    execvp (argv[command],&(argv[command]));
}