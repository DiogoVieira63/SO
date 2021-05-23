#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void loop_pipe(char ***cmd) {
    int p[2];
    pid_t pid;
    int fd_in = 0;

    while (*cmd != NULL) {
        if (pipe(p)) {
            fprintf(stderr, "Pipe failed.\n");
            return ;
        }
        if (!(pid = fork ())) {
            dup2(fd_in, STDIN_FILENO); //set input from previous commands
            if (*(cmd + 1) != NULL) //if there's a command next change the output to write in pipe
                dup2(p[1],STDOUT_FILENO); 
            close(p[0]);
            execvp((*cmd)[0], *cmd);
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            close(p[1]);
            fd_in = p[0];  //save the input for the next command
            cmd++;
        }
    }
}

//grep -v ^# /etc/passwd | cut -f7 -d: | uniq | wc -l.

int main() {
    char *grep[] = {"grep", "-v","^#","/etc/passwd",NULL};
    char *cut[] = {"cut","-f7","-d:",NULL};
    char *uniq[] = {"uniq", NULL};
    char *wc[]= {"wc","-l",NULL}; 
    char **cmd[] = {grep,cut,uniq,wc, NULL};


    int mypipe[2];
    int fd_in;
    pid_t pid;


    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    if (!fork()){
        close (mypipe[0]);
        dup2 (mypipe[1],STDOUT_FILENO);
        execlp ("grep","grep", "-v","^#","/etc/passwd",NULL);
    }
    else
    {
        close (mypipe[1]);
        fd_in =mypipe[0];
        wait (NULL);
    }


    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    if (!fork()){
        close (mypipe[0]);
        dup2 (fd_in,STDIN_FILENO);
        dup2 (mypipe[1],STDOUT_FILENO);
        execlp ("cut","cut","-f7","-d:",NULL);

    }
    else
    {
        close (mypipe[1]);
        fd_in =mypipe[0];
        wait (NULL);
    }
    
    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    if (!fork()){
        close (mypipe[0]);
        dup2 (fd_in,STDIN_FILENO);
        dup2 (mypipe[1],STDOUT_FILENO);
        execlp ("uniq","uniq", NULL); 

    }
    else
    {
        close (mypipe[1]);
        fd_in =mypipe[0];
        wait (NULL);
    }

    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    if (!fork()){
        close (mypipe[0]);
        dup2 (fd_in,STDIN_FILENO);
        execlp ("wc","wc","-l",NULL);

    }
    else
    {
        close (mypipe[1]);
        fd_in =mypipe[0];
        wait (NULL);
    }
    



    //loop_pipe(cmd);
    return (0);
}